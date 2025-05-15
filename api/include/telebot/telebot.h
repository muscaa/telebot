#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>
#include <map>

#include "telebot/api.h"

namespace telebot {

// init()
extern API SDL_Window* window;
extern API SDL_Renderer* renderer;
extern API ImGuiIO* io;
//extern SDL_Texture* texture_video_stream;
extern API std::map<SDL_Scancode, bool> key_states;

// run()
extern API bool running;
extern API int screen_width;
extern API int screen_height;

bool init();

void run();

void dispose();

}  // namespace telebot
