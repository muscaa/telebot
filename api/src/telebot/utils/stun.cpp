#include "telebot/utils/stun.h"

#include <unordered_map>

#include "telebot/utils/binary.h"
#include "telebot/utils/logging.h"

// packet ids

#define PACKET_S2C_CLIENTS 0x00
#define PACKET_C2S_LOGIN 0x01

namespace telebot::utils::stun {

namespace bin = telebot::utils::binary;
namespace log = telebot::utils::logging;

// server side

static std::unordered_map<std::string, int> clients;

static void send_s2c_clients(TcpServer* server) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_S2C_CLIENTS);

    bin::Int(data, offset, static_cast<int32_t>(clients.size()));
    for (const auto& [name, id] : clients) {
        bin::LenString(data, offset, name);
    }

    server->sendAll(data, offset);
}

static void receive_c2s_login(TcpServer* server, int id, const uint8_t* data, size_t& offset) {
    std::string name = bin::LenString(data, offset);

    if (clients.find(name) != clients.end()) {
        log::error("Client with name '{}' already exists", name);
        server->getConnections()[id]->close();
        return;
    }

    clients[name] = id;

    log::info("Client with ID {} connected as '{}'", id, name);
    send_s2c_clients(server);
}

struct StunServerObserver : TcpServer::Observer {
    void onConnectionAccepted(TcpServer* server, int id) {}

    void onReceived(TcpServer* server, int id, const uint8_t* data, size_t size) {
        size_t offset = 0;

        uint8_t packetId = bin::Byte(data, offset);
        switch (packetId) {
            case PACKET_C2S_LOGIN:
                receive_c2s_login(server, id, data, offset);
                break;
            default:
                log::error("Unknown packet ID: {}", packetId);
                break;
        }
    }
    
    void onConnectionClosed(TcpServer* server, int id) {
        for (auto it = clients.begin(); it != clients.end(); it++) {
            if (it->second == id) {
                clients.erase(it);
                break;
            }
        }

        send_s2c_clients(server);
    }
} serverObserver;

TcpServer* server(int port) {
    TcpServer* server = new TcpServer(serverObserver);
    server->listen(boost::asio::ip::tcp::v4(), port);
    server->startAcceptingConnections();

    return server;
}

// client side

static void receive_s2c_clients(TcpClient* client, const uint8_t* data, size_t& offset) {
    int size = bin::Int(data, offset);
    for (int i = 0; i < size; i++) {
        std::string name = bin::LenString(data, offset);

        log::info("Client {}: {}", i + 1, name);
    }
    log::info("---------------");
}

static void send_c2s_login(TcpClient* client, const std::string& name) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_C2S_LOGIN);
    bin::LenString(data, offset, name);

    client->send(data, offset);
}

struct StunClientObserver : TcpClient::Observer {
    std::string name;

    StunClientObserver(const std::string& name) : name(name) {}

    void onConnected(TcpClient* client) {
        send_c2s_login(client, name);
    }

    void onReceived(TcpClient* client, const uint8_t* data, size_t size) {
        size_t offset = 0;

        uint8_t packetId = bin::Byte(data, offset);
        switch (packetId) {
            case PACKET_S2C_CLIENTS:
                receive_s2c_clients(client, data, offset);
                break;
            default:
                log::error("Unknown packet ID: {}", packetId);
                break;
        }
    }
    
    void onDisconnected(TcpClient* client) {}
} clientObserver("hello");

TcpClient* client(std::string address, int port, std::string name) {
    TcpClient* client = new TcpClient(clientObserver);
    client->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port));

    return client;
}

} // namespace telebot::utils::stun
