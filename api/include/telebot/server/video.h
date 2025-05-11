#pragma once

#include <boost/asio.hpp>
#include <SDL3/SDL.h>

namespace telebot::server::video {

const int HEADER_SIZE = 8;

struct UDPVideoBuffer {
    boost::asio::ip::udp::endpoint clientEndpoint;
    uint8_t* buffer;
    size_t len;
    bool inUse;
};

bool is_running();

void start(int port, int threads, int max_size);

void update(SDL_Texture* texture);

void stop();

} // namespace telebot::server::video
