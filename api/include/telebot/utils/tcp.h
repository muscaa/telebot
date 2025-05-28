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
    boost::asio::ip::tcp::socket socket;
    ConnectionListener* listener;
    int id;

    bool reading;
    boost::asio::streambuf readBuffer;

    bool writing;
    boost::asio::streambuf writeBuffer;
    std::mutex writeBufferMutex;

    void doRead();

    void doWrite();

   public:
    Connection(boost::asio::ip::tcp::socket& socket, ConnectionListener* listener, int id = 0)
        : socket(std::move(socket)),
        listener(listener),
        id(id),
        reading(false),
        readBuffer(),
        writing(false),
        writeBuffer(),
        writeBufferMutex() {}

    void startReading();

    void send(const uint8_t* data, size_t size);

    void close();

    bool isOpen() const { return socket.is_open(); }

    boost::asio::ip::tcp::socket& getSocket() { return socket; }

    int getId() const { return id; }
};

struct ClientListener;
class Client;

struct ClientListener {
    virtual void onConnected(Client* client) = 0;

    virtual void onReceived(Client* client, const uint8_t* data, size_t size) = 0;

    virtual void onDisconnected(Client* client) = 0;
};

class Client : public ConnectionListener {
   private:
    std::shared_ptr<ClientListener> listener;
    
    boost::asio::io_context ioContext;
    std::thread thread;
    std::shared_ptr<Connection> connection;
    bool connecting;
   
    void onReceived(int id, const uint8_t* data, size_t size) override;

    void onConnectionClosed(int id) override;

   public:
    Client(const std::shared_ptr<ClientListener>& listener)
        : listener(listener),
        ioContext(),
        thread([this]() { ioContext.run(); }),
        connection(),
        connecting(false) {}

    void connect(const boost::asio::ip::address& address, boost::asio::ip::port_type port);

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

class Server : public ConnectionListener {
   private:
    std::shared_ptr<ServerListener> listener;

    boost::asio::io_context ioContext;
    std::thread thread;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_map<int, std::shared_ptr<Connection>> connections;
    int connectionIdCounter;
    bool accepting;
    bool closing;

    void onReceived(int id, const uint8_t* data, size_t size) override;
    
    void onConnectionClosed(int id) override;
    
    void doAccept();

   public:
    Server(const std::shared_ptr<ServerListener>& listener)
        : listener(listener),
        ioContext(),
        thread([this]() { ioContext.run(); }),
        acceptor(ioContext),
        connections(),
        connectionIdCounter(0),
        accepting(false),
        closing(false) {}

    bool listen(const boost::asio::ip::tcp& protocol, uint16_t port);

    void startAccepting();

    void send(int id, const uint8_t* data, size_t size);

    void sendAll(const uint8_t* data, size_t size);

    void close();

    bool isRunning() const { return acceptor.is_open(); }

    std::unordered_map<int, std::shared_ptr<Connection>>& getConnections() { return connections; }
};

} // namespace telebot::utils::tcp
