#include <telebot/utils/video.h>

#include <thread>

#include "telebot/utils/texture.h"

using boost::asio::ip::udp;

namespace telebot::utils::video {

static bool running = false;
static boost::asio::io_context* io_context;
static udp::socket* socket;
static UDPVideoBuffer* video_buffers[NUM_THREADS];
static std::thread* thread_pool[NUM_THREADS];

static void asyncReceive() {
    UDPVideoBuffer* video_buffer;
    for (int i = 0; i < NUM_THREADS; i++) {
        if (!video_buffers[i]->inUse) {
            video_buffer = video_buffers[i];
            video_buffer->inUse = true;
            break;
        }
    }

    socket->async_receive_from(
        boost::asio::buffer(video_buffer->buffer), video_buffer->clientEndpoint,
        [video_buffer](const boost::system::error_code& error, std::size_t bytesReceived) {
            asyncReceive();

            if (!error) {
                video_buffer->len = bytesReceived;
            }
        }
    );
}

bool is_video_server_running() {
    return running;
}

void start_video_server() {
    if (is_video_server_running()) {
        stop_video_server();
    }

    running = true;
    SDL_Log("Starting video server...\n");

    io_context = new boost::asio::io_context();
    socket = new udp::socket(*io_context, udp::endpoint(udp::v4(), BASE_PORT));

    for (int i = 0; i < NUM_THREADS; i++) {
        UDPVideoBuffer* video_buffer = new UDPVideoBuffer();
        video_buffer->inUse = false;
        video_buffer->len = 0;
        video_buffers[i] = video_buffer;
    }

    asyncReceive();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_pool[i] = new std::thread([]() {
            io_context->run();
        });
    }
}

void stream_video(SDL_Texture* texture) {
    if (!is_video_server_running()) return;

    for (int i = 0; i < NUM_THREADS; i++) {
        UDPVideoBuffer* video_buffer = video_buffers[i];
        if (!video_buffer->inUse || video_buffer->len <= HEADER_SIZE) continue;

        short frame_x = (video_buffer->buffer[0] & 0xFF) << 8 | (video_buffer->buffer[1] & 0xFF);
        short frame_y = (video_buffer->buffer[2] & 0xFF) << 8 | (video_buffer->buffer[3] & 0xFF);
        short frame_width = (video_buffer->buffer[4] & 0xFF) << 8 | (video_buffer->buffer[5] & 0xFF);
        short frame_height = (video_buffer->buffer[6] & 0xFF) << 8 | (video_buffer->buffer[7] & 0xFF);
        SDL_Rect rect = {frame_x, frame_y, frame_width, frame_height};

        telebot::utils::texture::update_texture(texture, video_buffer->buffer + HEADER_SIZE, video_buffer->len - HEADER_SIZE, &rect);

        video_buffer->len = 0;
        video_buffer->inUse = false;
    }
}

void stop_video_server() {
    if (!is_video_server_running()) return;

    running = false;
    SDL_Log("Stopping video server...\n");

    io_context->stop();
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_pool[i]->join();
        delete thread_pool[i];
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        delete video_buffers[i];
    }
}

} // namespace telebot::utils::video
