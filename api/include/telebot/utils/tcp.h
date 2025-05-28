#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace telebot::utils::tcp {

struct ConnectionListener;
class Connection;

struct ConnectionListener {
    virtual void onReceived(int id, const uint8_t* data, size_t size) = 0;

    virtual void onConnectionClosed(int id) = 0;
};

class Connection {
   private:
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;
    std::shared_ptr<ConnectionListener> listener;
    int id;

    bool isReading;
    boost::asio::streambuf readBuffer;

    bool isWritting;
    boost::asio::streambuf writeBuffer;
    std::mutex writeBufferMutex;

    Connection(std::unique_ptr<boost::asio::ip::tcp::socket>& socket, std::shared_ptr<ConnectionListener>& listener, int id = 0)
        : socket(std::move(socket)),
        listener(listener),
        id(id) {}

    void doRead();

    void doWrite();

   public:
    void startReading();

    void send(const uint8_t* data, size_t size);

    void close();

    bool isOpen() const { return socket->is_open(); }

    int getId() const { return id; }
};

struct ClientListener;
class Client;

struct ClientListener {
    virtual void onConnected(Client* client) = 0;

    virtual void onReceived(Client* client, const uint8_t* data, size_t size) = 0;

    virtual void onDisconnected(Client* client) = 0;
};

class Client : private ConnectionListener {
   private:
    std::shared_ptr<ClientListener> listener;
    
    boost::asio::io_context ioContext;
    std::thread thread;
    std::shared_ptr<Connection> connection;
    bool connecting;
   
    void onReceived(int id, const uint8_t* data, size_t size) override;

    void onConnectionClosed(int id) override;

   public:
    Client(std::shared_ptr<ClientListener>& listener)
        : listener(listener),
        thread([this]() { ioContext.run(); }) {}

    void connect(const boost::asio::ip::tcp::endpoint& endpoint);

    void send(const uint8_t* data, size_t size);

    void disconnect();

    bool isConnected() const { return (connection && connection->isOpen()) || connecting; }
};

struct ServerListener;
class Server;

struct ServerListener {
    virtual void onConnectionAccepted(Server* server, int id) = 0;

    virtual void onReceived(Server* server, int id, const uint8_t* data, size_t size) = 0;

    virtual void onConnectionClosed(Server* server, int id) = 0;
};

class Server : private ConnectionListener {
   private:
    std::shared_ptr<ServerListener> listener;

    boost::asio::io_context ioContext;
    std::thread thread;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_map<int, std::shared_ptr<Connection>> connections;
    int connectionIdCounter;
    bool isAccepting;
    bool isClosing;

    void onReceived(int id, const uint8_t* data, size_t size) override;
    
    void onConnectionClosed(int id) override;
    
    void doAccept();

   public:
    Server(std::shared_ptr<ServerListener>& listener)
        : listener(listener),
        thread([this]() { ioContext.run(); }),
        acceptor(ioContext) {}

    bool listen(const boost::asio::ip::tcp& protocol, uint16_t port);

    void startAccepting();

    void send(int id, const uint8_t* data, size_t size);

    void sendAll(const uint8_t* data, size_t size);

    void close();

    bool isRunning() const { return acceptor.is_open(); }

    std::unordered_map<int, std::shared_ptr<Connection>>& getConnections() { return connections; }
};

} // namespace telebot::utils::tcp
