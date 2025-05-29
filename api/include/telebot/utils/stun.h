#pragma once

#include <string>
#include <vector>

#include "telebot/utils/tcp.h"

namespace telebot::utils::stun {

namespace tcp = telebot::utils::tcp;

const uint8_t PACKET_S2C_LIST = 0x00;
const uint8_t PACKET_C2S_LOGIN = 0x01;

struct ClientListener;
class Client;

struct ClientListener : public tcp::ClientListener {
    void onConnected(tcp::Client* client) override;

    void onReceived(tcp::Client* client, const uint8_t* data, size_t size) override;

    void onDisconnected(tcp::Client* client) override;

    virtual void readS2CList(Client* client, const uint8_t* data, size_t& offset);

    virtual void sendC2SLogin(Client* client, const std::string& name);

    virtual void onList(Client* client, const std::vector<std::string>& list) = 0;
};

class Client : public tcp::Client {
   private:
    std::string name;

   public:
    Client(const std::shared_ptr<ClientListener>& listener, const std::string& name)
        : tcp::Client(listener),
        name(name) {}

    std::string getName() const { return name; }
};

struct ServerListener;
class Server;

struct ServerListener : public tcp::ServerListener {
    void onConnectionAccepted(tcp::Server* server, int id) override;

    void onReceived(tcp::Server* server, int id, const uint8_t* data, size_t size) override;

    void onConnectionClosed(tcp::Server* server, int id) override;

    virtual void sendS2CList(Server* server);

    virtual void readC2SLogin(Server* server, int id, const uint8_t* data, size_t& offset);
};

class Server : public tcp::Server {
   public:
    std::unordered_map<std::string, int> list;

    Server(const std::shared_ptr<ServerListener>& listener)
        : tcp::Server(listener) {}
};

} // namespace telebot::utils::stun
