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

// client

static void receive_s2c_clients(tcp::Client* client, const uint8_t* data, size_t& offset) {
    int size = bin::Int(data, offset);
    for (int i = 0; i < size; i++) {
        std::string name = bin::LenString(data, offset);

        log::info("{}", name);
    }
    log::info("---------------");
}

static void send_c2s_login(tcp::Client* client, const std::string& name) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_C2S_LOGIN);
    bin::LenString(data, offset, name);

    client->send(data, offset);
}

void ClientListener::onConnected(tcp::Client* client) {
    send_c2s_login(client, name);
}

void ClientListener::onReceived(tcp::Client* client, const uint8_t* data, size_t size) {
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

void ClientListener::onDisconnected(tcp::Client* client) {}

tcp::Client* client(std::string address, int port, std::string name) {
    std::shared_ptr<tcp::ClientListener> listener = std::make_shared<ClientListener>(name);
    tcp::Client* client = new tcp::Client(listener);
    client->connect(boost::asio::ip::make_address(address), port);
    return client;
}

// server

static std::unordered_map<std::string, int> clients;

static void send_s2c_clients(tcp::Server* server) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_S2C_CLIENTS);

    bin::Int(data, offset, static_cast<int32_t>(clients.size()));
    for (const auto& [name, id] : clients) {
        bin::LenString(data, offset, name);
    }

    server->sendAll(data, offset);
}

static void receive_c2s_login(tcp::Server* server, int id, const uint8_t* data, size_t& offset) {
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

void ServerListener::onConnectionAccepted(tcp::Server* server, int id) {
    log::info("Client with ID {} joined", id);
}

void ServerListener::onReceived(tcp::Server* server, int id, const uint8_t* data, size_t size) {
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

void ServerListener::onConnectionClosed(tcp::Server* server, int id) {
    for (auto it = clients.begin(); it != clients.end(); it++) {
        if (it->second == id) {
            clients.erase(it);
            break;
        }
    }

    send_s2c_clients(server);
}

tcp::Server* server(int port) {
    std::shared_ptr<tcp::ServerListener> listener = std::make_shared<ServerListener>();
    tcp::Server* server = new tcp::Server(listener);
    server->listen(boost::asio::ip::tcp::v4(), port);
    server->startAccepting();
    return server;
}

} // namespace telebot::utils::stun
