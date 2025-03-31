#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>

namespace TeleBot {

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern ImGuiIO *io;
extern bool running;

bool Init();

void Render();

void Dispose();

}  // namespace TeleBot
