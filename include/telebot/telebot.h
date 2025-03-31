#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>

namespace telebot {

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern ImGuiIO* io;
extern bool running;

bool init();

void run();

void dispose();

}  // namespace telebot
