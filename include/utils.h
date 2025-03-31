#pragma once

#include <SDL3/SDL.h>
#include <imgui.h>

namespace TeleBot {

bool LoadTextureFromMemory(const void* data, size_t data_size, SDL_Renderer* renderer, SDL_Texture** out_texture, int* out_width, int* out_height);

bool LoadTextureFromFile(const char* file_name, SDL_Renderer* renderer, SDL_Texture** out_texture, int* out_width, int* out_height);

}  // namespace TeleBot
