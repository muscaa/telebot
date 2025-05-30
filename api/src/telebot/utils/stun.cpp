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
        case PACKET_S2C_LINK_REQUEST:
            readS2CLinkRequest(stunClient, data, offset);
            break;
        case PACKET_S2C_LINK_RESPONSE:
            readS2CLinkResponse(stunClient, data, offset);
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

void ClientListener::sendC2SLinkRequest(Client* client, const std::string& name) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_C2S_LINK_REQUEST);
    bin::LenString(data, offset, name);

    client->send(data, offset);
}

void ClientListener::readS2CLinkRequest(Client* client, const uint8_t* data, size_t& offset) {
    std::string from = bin::LenString(data, offset);

    onLinkRequest(client, from);
}

void ClientListener::sendC2SLinkResponse(Client* client, const std::string& name, bool accept) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_C2S_LINK_RESPONSE);
    bin::LenString(data, offset, name);
    bin::Bool(data, offset, accept);

    client->send(data, offset);
}

void ClientListener::readS2CLinkResponse(Client* client, const uint8_t* data, size_t& offset) {
    std::string name = bin::LenString(data, offset);
    bool accept = bin::Bool(data, offset);

    if (accept) {
        std::string ip = bin::LenString(data, offset);
        uint16_t port = bin::Short(data, offset);

        onLinkAccepted(client, name, ip, port);
    } else {
        std::string declineMessage = bin::LenString(data, offset);

        onLinkDeclined(client, name, declineMessage);
    }
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
        case PACKET_C2S_LINK_REQUEST:
            readC2SLinkRequest(stunServer, id, data, offset);
            break;
        case PACKET_C2S_LINK_RESPONSE:
            readC2SLinkResponse(stunServer, id, data, offset);
            break;
        default:
            log::error("Unknown packet ID: {}", packetId);
            break;
    }
}

void ServerListener::onConnectionClosed(tcp::Server* server, int id) {
    log::info("Client with ID {} left", id);

    Server* stunServer = server->as<Server>();

    if (stunServer->id2Name.contains(id)) {
        std::string name = stunServer->id2Name[id];

        stunServer->id2Name.erase(id);
        stunServer->name2Id.erase(name);

        sendS2CList(stunServer);
    }
}

void ServerListener::sendS2CList(Server* server) {
    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_S2C_LIST);

    bin::Int(data, offset, static_cast<int32_t>(server->id2Name.size()));
    for (const auto& [id, name] : server->id2Name) {
        bin::LenString(data, offset, name);
    }

    server->sendAll(data, offset);
}

void ServerListener::readC2SLogin(Server* server, int id, const uint8_t* data, size_t& offset) {
    std::string name = bin::LenString(data, offset);

    if (server->name2Id.contains(name)) {
        log::error("Client with name '{}' already exists", name);
        server->getConnections()[id]->close();
        return;
    }

    server->id2Name[id] = name;
    server->name2Id[name] = id;

    log::info("Client with ID {} connected as '{}'", id, name);
    sendS2CList(server);
}

void ServerListener::readC2SLinkRequest(Server* server, int id, const uint8_t* data, size_t& offset) {
    if (!server->id2Name.contains(id)) {
        log::error("Client with ID {} not logged in", id);
        server->getConnections()[id]->close();
        return;
    }

    std::string from = server->id2Name[id];
    std::string to = bin::LenString(data, offset);

    if (!server->name2Id.contains(to)) {
        log::error("Client with name '{}' not found", to);
        server->getConnections()[id]->close();
        return;
    }

    sendS2CLinkRequest(server, from, to);
}

void ServerListener::sendS2CLinkRequest(Server* server, const std::string& from, const std::string& to) {
    int idFrom = server->name2Id[from];
    int idTo = server->name2Id[to];

    if (server->linkRequests.contains(idFrom) || server->linkRequests.contains(idTo)) {
        log::error("Cannot send link request from '{}' to '{}'", from, to);
        return;
    }

    server->linkRequests[idFrom] = idTo;

    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_S2C_LINK_REQUEST);
    bin::LenString(data, offset, from);

    server->send(idTo, data, offset);
}

void ServerListener::readC2SLinkResponse(Server* server, int id, const uint8_t* data, size_t& offset) {
    std::string from = bin::LenString(data, offset);
    int idFrom = server->name2Id[from];
    std::string to = server->id2Name[id];
    int idTo = id;

    if (!server->linkRequests.contains(idFrom) || server->linkRequests[idFrom] != idTo) {
        log::error("Link request from '{}' to '{}' not found", from, to);
        server->getConnections()[id]->close();
        return;
    }

    server->linkRequests.erase(idFrom);

    bool accept = bin::Bool(data, offset);
    if (accept) {
        sendS2CLinkResponse(server, from, to, true);
    } else {
        sendS2CLinkResponse(server, from, to, false);
    }
}

void ServerListener::sendS2CLinkResponse(Server* server, const std::string& from, const std::string& to, bool accept, const std::string& declineMessage) {
    int idFrom = server->name2Id[from];
    int idTo = server->name2Id[to];

    uint8_t data[1024];
    size_t offset = 0;

    bin::Byte(data, offset, PACKET_S2C_LINK_RESPONSE);

    if (!accept) {
        bin::LenString(data, offset, to);
        bin::Bool(data, offset, false);
        bin::LenString(data, offset, declineMessage);

        server->send(idFrom, data, offset);
        return;
    }

    {
        bin::LenString(data, offset, to);
        bin::Bool(data, offset, true);

        boost::asio::ip::tcp::endpoint endpointTo = server->getConnections()[idTo]->getSocket().remote_endpoint();
        std::string ipTo = endpointTo.address().to_string();
        uint16_t portTo = endpointTo.port();

        bin::LenString(data, offset, ipTo);
        bin::Short(data, offset, portTo);

        server->send(idFrom, data, offset);
    }

    offset = 1;

    {
        bin::LenString(data, offset, from);
        bin::Bool(data, offset, true);

        boost::asio::ip::tcp::endpoint endpointFrom = server->getConnections()[idFrom]->getSocket().remote_endpoint();
        std::string ipFrom = endpointFrom.address().to_string();
        uint16_t portFrom = endpointFrom.port();

        bin::LenString(data, offset, ipFrom);
        bin::Short(data, offset, portFrom);

        server->send(idTo, data, offset);
    }
}

} // namespace telebot::utils::stun
