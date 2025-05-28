#pragma once

#include <string>
//#include <TcpServer.hpp>
//#include <TcpClient.hpp>

#include "telebot/utils/tcp.h"

namespace telebot::utils::stun {

namespace tcp = telebot::utils::tcp;

struct ClientListener;

struct ClientListener : public tcp::ClientListener {
    std::string name;

    ClientListener(const std::string& name)
        : name(name) {}

    void onConnected(tcp::Client* client) override;

    void onReceived(tcp::Client* client, const uint8_t* data, size_t size) override;

    void onDisconnected(tcp::Client* client) override;
};

tcp::Client* client(std::string address, int port, std::string name);

struct ServerListener;

struct ServerListener : public tcp::ServerListener {
    void onConnectionAccepted(tcp::Server* server, int id) override;

    void onReceived(tcp::Server* server, int id, const uint8_t* data, size_t size) override;

    void onConnectionClosed(tcp::Server* server, int id) override;
};

tcp::Server* server(int port);

} // namespace telebot::utils::stun
