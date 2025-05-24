#include "telebot/utils/stun.h"

#include "telebot/utils/binary.h"
#include <iostream>

namespace telebot::utils::stun {

namespace bin = telebot::utils::binary;

static void write_clients(TcpServer* server) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Int(data, static_cast<int32_t>(server->getConnections().size()), offset);
    for (const auto& [id, connection] : server->getConnections()) {
        bin::Int(data, id, offset);
    }

    server->sendAll(data, offset);
}

static void read_clients(TcpClient* client, const uint8_t* data) {
    size_t offset = 0;

    int clients = bin::Int(data, offset);
    for (int i = 0; i < clients; i++) {
        int id = bin::Int(data, offset);

        std::cout << id << ", ";
    }
    std::cout << std::endl;
}

TcpServer* server(int port) {
    struct : TcpServer::Observer {
        void onConnectionAccepted(TcpServer* server, int id) {
            write_clients(server);
        }

        void onReceived(TcpServer* server, int id, const uint8_t* data, size_t size) {

        }
        
        void onConnectionClosed(TcpServer* server, int id) {
            write_clients(server);
        }
    } observer;

    TcpServer* server = new TcpServer(observer);
    server->listen(boost::asio::ip::tcp::v4(), port);
    server->startAcceptingConnections();

    return server;
}

TcpClient* client(std::string address, int port) {
    struct : TcpClient::Observer {
        void onConnected(TcpClient* client) {

        }

        void onReceived(TcpClient* client, const uint8_t* data, size_t size) {
            read_clients(client, data);
        }
        
        void onDisconnected(TcpClient* client) {

        }
    } observer;

    TcpClient* client = new TcpClient(observer);
    client->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port));

    return client;
}

} // namespace telebot::utils::stun
