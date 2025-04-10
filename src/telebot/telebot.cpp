#include "telebot/telebot.h"

#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <string>
#include <cstddef>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <map>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

#include "telebot/utils/texture.h"
#include "telebot/utils/socket.h"

namespace telebot {

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
ImGuiIO* io = nullptr;
bool running = false;

bool init() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Telebot", 1280, 720, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        SDL_Log("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    //SDL_SetRenderVSync(renderer, 1);
    if (renderer == nullptr) {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return false;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    return true;
}

const static int JPEG_MAX_SIZE = 128000;
const static int NUM_THREADS = 32;
const static int BASE_PORT = 4444;
static boost::asio::io_context io_context;

struct ThreadBuffer {
    bool inUse;
    size_t len;
    unsigned char buffer[JPEG_MAX_SIZE / NUM_THREADS];
    udp::endpoint client_endpoint;
};

static udp::socket socket(io_context, udp::endpoint(udp::v4(), BASE_PORT));
static ThreadBuffer* threadBuffers[NUM_THREADS];
static std::thread* pool[NUM_THREADS];

static void asyncReceive() {
    ThreadBuffer* threadBuffer;
    for (int i = 0; i < NUM_THREADS; i++) {
        if (!threadBuffers[i]->inUse) {
            threadBuffer = threadBuffers[i];
            threadBuffer->inUse = true;
            break;
        }
    }

    socket.async_receive_from(
        boost::asio::buffer(threadBuffer->buffer), threadBuffer->client_endpoint,
        [threadBuffer](const boost::system::error_code& error, std::size_t bytesReceived) {
            asyncReceive();

            if (!error) {
                threadBuffer->len = bytesReceived;
            }
        }
    );
}

void run() {
    running = true;

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    SDL_Texture* my_texture = telebot::utils::load_texture_from_file(renderer, "image.jpg");
    SDL_Texture* telebot_video = telebot::utils::create_texture_streaming(renderer, 1280, 720);

    for (int i = 0; i < NUM_THREADS; i++) {
        ThreadBuffer* threadBuffer = new ThreadBuffer();
        threadBuffer->inUse = false;
        threadBuffer->len = 0;
        threadBuffers[i] = threadBuffer;
    }

    asyncReceive();

    for (int i = 0; i < NUM_THREADS; i++) {
        pool[i] = new std::thread([]() {
            io_context.run();
        });
    }

    // Main loop
    while (running) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        // [If using SDL_MAIN_USE_CALLBACKS: call ImGui_ImplSDL3_ProcessEvent() from your SDL_AppEvent() function]
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            
            if ((event.type == SDL_EVENT_QUIT) 
                || (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED
                    && event.window.windowID == SDL_GetWindowID(window))
                //||
                ) {
                running = false;
            }
        }

        // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppIterate() function]
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
            SDL_Delay(10);
            continue;
        }
        
        for (int i = 0; i < NUM_THREADS; i++) {
            ThreadBuffer* threadBuffer = threadBuffers[i];
            if (!threadBuffer->inUse) {
                continue;
            }

            if (threadBuffer->len > 8) {
                short frame_x = (threadBuffer->buffer[0] & 0xFF) << 8 | (threadBuffer->buffer[1] & 0xFF);
                short frame_y = (threadBuffer->buffer[2] & 0xFF) << 8 | (threadBuffer->buffer[3] & 0xFF);
                short frame_width = (threadBuffer->buffer[4] & 0xFF) << 8 | (threadBuffer->buffer[5] & 0xFF);
                short frame_height = (threadBuffer->buffer[6] & 0xFF) << 8 | (threadBuffer->buffer[7] & 0xFF);
                SDL_Rect rect = {frame_x, frame_y, frame_width, frame_height};

                telebot::utils::update_texture(telebot_video, reinterpret_cast<std::byte*>(threadBuffer->buffer + 8), threadBuffer->len - 8, &rect);

                threadBuffer->len = 0;
                threadBuffer->inUse = false;
            }
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*) &clear_color);// Edit 3 floats representing a color

            if (ImGui::Button("Button")) {                          // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            if (ImGui::Button("Server")) {
                telebot::utils::start_server();
            }
            ImGui::SameLine();
            if (ImGui::Button("Client")) {
                telebot::utils::start_client();
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
            ImGui::Image((ImTextureID)(intptr_t) my_texture, ImVec2(my_texture->w, my_texture->h));
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window) {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me")) {
                show_another_window = false;
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        //SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);

        if (my_texture) {
            SDL_FRect destRect = {200, 150, 400, 300};  // x, y, width, height
            SDL_RenderTexture(renderer, my_texture, nullptr, &destRect);
        }

        if (telebot_video != nullptr) {
            SDL_FRect destRect = {0, 0, 1280, 720};
            SDL_RenderTexture(renderer, telebot_video, nullptr, &destRect);
        }

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    io_context.stop();
    for (int i = 0; i < NUM_THREADS; i++) {
        pool[i]->join();
        delete pool[i];
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        delete threadBuffers[i];
    }
}

void dispose() {
    running = false;

    // Cleanup
    // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppQuit() function]
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

}  // namespace telebot
