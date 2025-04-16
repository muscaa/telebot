#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>

namespace telebot {

// init()
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern ImGuiIO* io;
extern SDL_Texture* texture_video_stream;

// run()
extern bool running;
extern int screen_width;
extern int screen_height;

bool init();

void run();

void dispose();

}  // namespace telebot
