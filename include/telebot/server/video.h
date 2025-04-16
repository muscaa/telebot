#pragma once

#include <boost/asio.hpp>
#include <SDL3/SDL.h>

namespace telebot::server::video {

const int JPEG_MAX_SIZE = 128000;
const int NUM_THREADS = 32;
const int BASE_PORT = 4444;
const int HEADER_SIZE = 8;

struct UDPVideoBuffer {
    boost::asio::ip::udp::endpoint clientEndpoint;
    uint8_t buffer[JPEG_MAX_SIZE / NUM_THREADS];
    size_t len;
    bool inUse;
};

bool is_running();

void start();

void update(SDL_Texture* texture);

void stop();

} // namespace telebot::server::video
