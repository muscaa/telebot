#include "telebot/utils/stun.h"

namespace telebot::utils::stun {

TcpServer* server(int port) {
    struct : TcpServer::Observer {
        void onConnectionAccepted(TcpServer* server, int id) {

        }

        void onReceived(TcpServer* server, int id, const char* data, size_t size) {

        }
        
        void onConnectionClosed(TcpServer* server, int id) {

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

        void onReceived(TcpClient* client, const char* data, size_t size) {

        }
        
        void onDisconnected(TcpClient* client) {

        }
    } observer;

    TcpClient* client = new TcpClient(observer);
    client->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port));

    return client;
}

} // namespace telebot::utils::stun
