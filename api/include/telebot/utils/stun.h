#pragma once

#include <string>
#include <vector>

#include "telebot/utils/tcp.h"

namespace telebot::utils::stun {

namespace tcp = telebot::utils::tcp;

const uint8_t PACKET_S2C_LIST = 0x00;
const uint8_t PACKET_C2S_LOGIN = 0x01;
const uint8_t PACKET_C2S_LINK_REQUEST = 0x02;
const uint8_t PACKET_S2C_LINK_REQUEST = 0x03;
const uint8_t PACKET_C2S_LINK_RESPONSE = 0x04;
const uint8_t PACKET_S2C_LINK_RESPONSE = 0x05;

struct ClientListener;
class Client;

struct ClientListener : public tcp::ClientListener {
    void onConnected(tcp::Client* client) override;

    void onReceived(tcp::Client* client, const uint8_t* data, size_t size) override;

    void onDisconnected(tcp::Client* client) override;

    virtual void readS2CList(Client* client, const uint8_t* data, size_t& offset);

    virtual void sendC2SLogin(Client* client, const std::string& name);

    virtual void sendC2SLinkRequest(Client* client, const std::string& name);

    virtual void readS2CLinkRequest(Client* client, const uint8_t* data, size_t& offset);

    virtual void sendC2SLinkResponse(Client* client, const std::string& name, bool accept);

    virtual void readS2CLinkResponse(Client* client, const uint8_t* data, size_t& offset);

    virtual void onList(Client* client, const std::vector<std::string>& list) = 0;

    virtual void onLinkRequest(Client* client, const std::string& from) = 0;

    virtual void onLinkAccepted(Client* client, const std::string& name, const std::string& myip, int myport, const std::string& ip, int port) = 0;

    virtual void onLinkDeclined(Client* client, const std::string& name, const std::string& message) = 0;
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

    virtual void readC2SLinkRequest(Server* server, int id, const uint8_t* data, size_t& offset);

    virtual void sendS2CLinkRequest(Server* server, const std::string& from, const std::string& to);

    virtual void readC2SLinkResponse(Server* server, int id, const uint8_t* data, size_t& offset);

    virtual void sendS2CLinkResponse(Server* server, const std::string& from, const std::string& to, bool accept, const std::string& declineMessage = "Link request declined");
};

class Server : public tcp::Server {
   public:
    std::unordered_map<int, std::string> id2Name;
    std::unordered_map<std::string, int> name2Id;
    std::unordered_map<int, int> linkRequests;

    Server(const std::shared_ptr<ServerListener>& listener)
        : tcp::Server(listener) {}
};

} // namespace telebot::utils::stun
