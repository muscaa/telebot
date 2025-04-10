#pragma once

#include <cstddef>
#include <string>
#include <SDL3/SDL.h>

namespace telebot::utils {

SDL_Texture* load_texture_from_memory(SDL_Renderer* renderer, const std::byte* data, const size_t data_size);

SDL_Texture* load_texture_from_file(SDL_Renderer* renderer, const std::string file_name);

bool update_texture(SDL_Texture* texture, const std::byte* data, const size_t data_size, const SDL_Rect* rect = nullptr);

SDL_Texture* create_texture_streaming(SDL_Renderer* renderer, int width, int height);

}  // namespace telebot::utils
