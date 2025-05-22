#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <boost/asio.hpp>
#include <memory>

#include "TcpConnection.hpp"

class TcpClient : private TcpConnection::Observer {
   public:
    struct Observer {
        virtual void onConnected(const TcpClient& client);
        virtual void onReceived(const TcpClient& client, const char* data, size_t size);
        virtual void onDisconnected(const TcpClient& client);
    };

    TcpClient(const Observer& observer);

    void connect(const boost::asio::ip::tcp::endpoint& endpoint);
    void send(const char* data, size_t size);
    void disconnect();
    bool isConnected() const { return m_connection->isOpen(); }

   private:
    void onReceived(int connectionId, const char* data, size_t size) override;
    void onConnectionClosed(int connectionId) override;

    boost::asio::io_context m_ioContext;
    std::thread m_thread;
    std::shared_ptr<TcpConnection> m_connection;
    Observer m_observer;
};

#endif
