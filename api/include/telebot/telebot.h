#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>
#include <map>

namespace telebot {

// init()
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern ImGuiIO* io;
//extern SDL_Texture* texture_video_stream;
extern std::map<SDL_Scancode, bool> key_states;

// run()
extern bool running;
extern int screen_width;
extern int screen_height;

bool init();

void run();

void dispose();

}  // namespace telebot
