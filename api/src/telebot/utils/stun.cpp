#include "telebot/utils/stun.h"

#include <vector>

namespace telebot::utils::stun {

static void send_clients(TcpServer* server) {
    std::vector<uint8_t> response;
    for (const auto& [id, connection] : server->getConnections()) {
        response.push_back(id);
    }

    server->sendAll(response.data(), response.size());
}

TcpServer* server(int port) {
    struct : TcpServer::Observer {
        void onConnectionAccepted(TcpServer* server, int id) {
            send_clients(server);
        }

        void onReceived(TcpServer* server, int id, const uint8_t* data, size_t size) {

        }
        
        void onConnectionClosed(TcpServer* server, int id) {
            send_clients(server);
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

        }
        
        void onDisconnected(TcpClient* client) {

        }
    } observer;

    TcpClient* client = new TcpClient(observer);
    client->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port));

    return client;
}

} // namespace telebot::utils::stun
