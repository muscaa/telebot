#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <mutex>

namespace telebot::utils::tcp {

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

struct ClientListener {
    virtual void onConnected(TcpClient* client) = 0;

    virtual void onReceived(TcpClient* client, const uint8_t* data, size_t size) = 0;

    virtual void onDisconnected(TcpClient* client) = 0;
};

class TcpClient : private TcpConnection::Observer {
   public:
    TcpClient(Observer& observer);

    void connect(const boost::asio::ip::tcp::endpoint& endpoint);
    void send(const uint8_t* data, size_t size);
    void disconnect();
    bool isConnected() const { return (m_connection && m_connection->isOpen()) || connecting; }

   private:
    void onReceived(int id, const uint8_t* data, size_t size) override;
    void onConnectionClosed(int id) override;

    bool connecting;
    boost::asio::io_context m_ioContext;
    std::thread m_thread;
    std::shared_ptr<TcpConnection> m_connection;
    Observer& m_observer;
};

} // namespace telebot::utils::tcp
