#include "telebot/cli/cli.h"

#include <iostream>
#include <TcpServer.hpp>
#include <TcpClient.hpp>

#include "telebot/utils/logging.h"

namespace telebot::cli {

namespace log = telebot::utils::logging;

static void stun_server() {
    struct : TcpServer::Observer {
        void onConnectionAccepted(int id) {
            std::cout << "New client connected with id " << id << std::endl;
        }
        void onConnectionClosed(int id) {
            std::cout << "Client " << id << " disconnected" << std::endl;
        }
        void onReceived(int id, const char* data, size_t size) {
            std::cout << "Data received from client " << id << ": ";
            std::cout.write(data, size);
            std::cout << std::endl;
        }
    } observer;

    boost::asio::io_context context;
    std::thread thread{[&context]() { context.run(); }};

    TcpServer server{context, observer};
    server.listen(boost::asio::ip::tcp::v4(), 1234);
    server.startAcceptingConnections();
}

static void stun_client() {
    struct : TcpClient::Observer {
        void onConnected() {
            std::cout << "Client connected" << std::endl;
        }
        void onDisconnected() {
            std::cout << "Client disconnected" << std::endl;
        }
        void onReceived(const char* data, size_t size) {
            std::cout << "Data received from server: ";
            std::cout.write(data, size);
            std::cout << std::endl;
        }
    } observer;

    boost::asio::io_context context;
    std::thread thread{[&context]() { context.run(); }};

    TcpClient client{context, observer};
    client.connect({boost::asio::ip::make_address("127.0.0.1"), 1234});
}

int main(const std::vector<std::string>& args) {
    log::info("telebot::cli::main() called with {} arguments", args.size());
    return 0;
}

} // namespace telebot::cli
