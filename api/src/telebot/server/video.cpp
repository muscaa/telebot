#include "telebot/server/video.h"

#include <thread>
#include <array>

#include "telebot/utils/texture.h"

using boost::asio::ip::udp;

namespace telebot::server::video {

static bool running;
static int num_threads;
static int size_per_thread;
static boost::asio::io_context* io_context;
static udp::socket* socket;
static UDPVideoBuffer** video_buffers;
static std::thread** thread_pool;

static void async_receive() {
    UDPVideoBuffer* video_buffer;
    for (int i = 0; i < num_threads; i++) {
        if (!video_buffers[i]->inUse) {
            video_buffer = video_buffers[i];
            video_buffer->inUse = true;
            break;
        }
    }

    socket->async_receive_from(
        boost::asio::buffer(video_buffer->buffer, size_per_thread), video_buffer->clientEndpoint,
        [video_buffer](const boost::system::error_code& error, std::size_t bytesReceived) {
            async_receive();

            if (!error) {
                video_buffer->len = bytesReceived;
            }
        }
    );
}

bool is_running() {
    return running;
}

void start(int port, int threads, int max_size) {
    if (is_running()) {
        stop();
    }

    running = true;
    SDL_Log("Starting video server...\n");

    num_threads = threads;
    size_per_thread = max_size / threads;

    io_context = new boost::asio::io_context();
    socket = new udp::socket(*io_context, udp::endpoint(udp::v4(), port));

    video_buffers = new UDPVideoBuffer*[threads];
    for (int i = 0; i < threads; i++) {
        UDPVideoBuffer* video_buffer = new UDPVideoBuffer();
        video_buffer->buffer = new uint8_t[size_per_thread];
        video_buffer->len = 0;
        video_buffer->inUse = false;
        video_buffers[i] = video_buffer;
    }

    async_receive();

    thread_pool = new std::thread*[threads];
    for (int i = 0; i < threads; i++) {
        thread_pool[i] = new std::thread([]() {
            io_context->run();
        });
    }
}

void update(SDL_Texture* texture) {
    if (!is_running()) return;

    for (int i = 0; i < num_threads; i++) {
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

void stop() {
    if (!is_running()) return;

    running = false;
    SDL_Log("Stopping video server...\n");

    io_context->stop();
    for (int i = 0; i < num_threads; i++) {
        thread_pool[i]->join();
        delete thread_pool[i];
    }
    delete[] thread_pool;

    for (int i = 0; i < num_threads; i++) {
        delete video_buffers[i]->buffer;
        delete video_buffers[i];
    }
    delete[] video_buffers;
}

} // namespace telebot::server::video
