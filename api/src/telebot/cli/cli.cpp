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
    std::thread thread([&context]() { context.run(); });

    TcpServer server(context, observer);
    server.listen(boost::asio::ip::tcp::v4(), 1234);
    server.startAcceptingConnections();

    while (server.isRunning()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    log::info("Server is shutting down...");
}

static TcpClient* client;

static void stun_client() {
    struct : TcpClient::Observer {
        void onConnected() {
            std::cout << "Client connected" << std::endl;

            client->send("Hello, server!", 15);
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
    std::thread thread([&context]() { context.run(); });

    client = new TcpClient(context, observer);
    client->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 1234));

    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (client->isConnected()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(const std::vector<std::string>& args) {
    log::info("telebot::cli::main() called with {} arguments", args.size());

    if (args.size() < 2) {
        log::error("Usage: {} <server|client>", args[0]);
        return 1;
    }

    if (args[1] == "server") {
        log::info("Starting STUN server...");
        stun_server();
    } else if (args[1] == "client") {
        log::info("Starting STUN client...");
        stun_client();
    } else {
        log::error("Unknown mode: {}", args[1]);
        return 1;
    }

    return 0;
}

} // namespace telebot::cli
