#include "telebot/utils/texture.h"

#include <fstream>
#include <vector>
#include <iterator>

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace telebot::utils::texture {

SDL_Texture* load_texture_from_memory(SDL_Renderer* renderer, const uint8_t* data, const size_t data_size) {
    const int channels = 4;

    int width = 0;
    int height = 0;

    uint8_t* image_bytes = stbi_load_from_memory(
        data,
        data_size,
        &width,
        &height,
        nullptr,
        channels
    );
    if (image_bytes == nullptr) {
        SDL_Log("Failed to load image: %s", stbi_failure_reason());
        return nullptr;
    }

    SDL_Surface* surface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, image_bytes, channels * width);
    if (surface == nullptr) {
        stbi_image_free(image_bytes);

        SDL_Log("Failed to create SDL surface: %s", SDL_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    stbi_image_free(image_bytes);
    if (texture == nullptr) {
        SDL_Log("Failed to create SDL texture: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}

SDL_Texture* load_texture_from_file(SDL_Renderer* renderer, const std::string file_name) {
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if (!file) {
        SDL_Log("Could not open file: %s", file_name.c_str());
        return nullptr;
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(file_size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), file_size)) {
        SDL_Log("Error reading file: %s", file_name.c_str());
        return nullptr;
    }

    return load_texture_from_memory(renderer, buffer.data(), buffer.size());
}

bool update_texture(SDL_Texture* texture, const uint8_t* data, const size_t data_size, const SDL_Rect* rect) {
    if (texture == nullptr) return false;

    const int channels = 4;

    int width = 0;
    int height = 0;

    uint8_t* image_bytes = stbi_load_from_memory(
        data,
        data_size,
        &width,
        &height,
        nullptr,
        channels
    );
    if (image_bytes == nullptr) {
        SDL_Log("Failed to load image: %s", stbi_failure_reason());
        return false;
    }

    bool result = SDL_UpdateTexture(texture, rect, image_bytes, channels * width);
    stbi_image_free(image_bytes);
    return result;
}

SDL_Texture* create_texture_streaming(SDL_Renderer* renderer, int width, int height) {
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (texture == nullptr) {
        SDL_Log("Failed to create SDL texture: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}

void delete_texture(SDL_Texture* texture) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

}  // namespace telebot::utils
