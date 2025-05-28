#include "telebot/utils/stun.h"

#include <unordered_map>

#include "telebot/utils/binary.h"
#include "telebot/utils/logging.h"

namespace telebot::utils::stun {

namespace bin = telebot::utils::binary;
namespace log = telebot::utils::logging;

// client

void ClientListener::onConnected(tcp::Client* client) {
    Client* stunClient = client->as<Client>();

    sendC2SLogin(stunClient, stunClient->getName());
}

void ClientListener::onReceived(tcp::Client* client, const uint8_t* data, size_t size) {
    Client* stunClient = client->as<Client>();
    size_t offset = 0;

    uint8_t packetId = bin::Byte(data, offset);
    switch (packetId) {
        case PACKET_S2C_LIST:
            readS2CList(stunClient, data, offset);
            break;
        default:
            log::error("Unknown packet ID: {}", packetId);
            break;
    }
}

void ClientListener::onDisconnected(tcp::Client* client) {}

void ClientListener::readS2CList(Client* client, const uint8_t* data, size_t& offset) {
    std::vector<std::string> list;

    int size = bin::Int(data, offset);
    for (int i = 0; i < size; i++) {
        std::string name = bin::LenString(data, offset);

        list.push_back(name);
    }

    onList(client, list);
}

void ClientListener::sendC2SLogin(Client* client, const std::string& name) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_C2S_LOGIN);
    bin::LenString(data, offset, name);

    client->send(data, offset);
}

// server

void ServerListener::onConnectionAccepted(tcp::Server* server, int id) {
    log::info("Client with ID {} joined", id);
}

void ServerListener::onReceived(tcp::Server* server, int id, const uint8_t* data, size_t size) {
    Server* stunServer = server->as<Server>();
    size_t offset = 0;

    uint8_t packetId = bin::Byte(data, offset);
    switch (packetId) {
        case PACKET_C2S_LOGIN:
            readC2SLogin(stunServer, id, data, offset);
            break;
        default:
            log::error("Unknown packet ID: {}", packetId);
            break;
    }
}

void ServerListener::onConnectionClosed(tcp::Server* server, int id) {
    Server* stunServer = server->as<Server>();

    for (auto it = stunServer->list.begin(); it != stunServer->list.end(); it++) {
        if (it->second == id) {
            stunServer->list.erase(it);
            sendS2CList(stunServer);
            break;
        }
    }
}

void ServerListener::sendS2CList(Server* server) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_S2C_LIST);

    bin::Int(data, offset, static_cast<int32_t>(server->list.size()));
    for (const auto& [name, id] : server->list) {
        bin::LenString(data, offset, name);
    }

    server->sendAll(data, offset);
}

void ServerListener::readC2SLogin(Server* server, int id, const uint8_t* data, size_t& offset) {
    std::string name = bin::LenString(data, offset);

    if (server->list.find(name) != server->list.end()) {
        log::error("Client with name '{}' already exists", name);
        server->getConnections()[id]->close();
        return;
    }

    server->list[name] = id;

    log::info("Client with ID {} connected as '{}'", id, name);
    sendS2CList(server);
}

} // namespace telebot::utils::stun
