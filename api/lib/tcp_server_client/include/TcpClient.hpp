#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <boost/asio.hpp>
#include <memory>

#include "TcpConnection.hpp"

class TcpClient : private TcpConnection::Observer {
   public:
    struct Observer {
        virtual void onConnected(TcpClient* client);
        virtual void onReceived(TcpClient* client, const uint8_t* data, size_t size);
        virtual void onDisconnected(TcpClient* client);
    };

    TcpClient(const Observer& observer);

    void connect(const boost::asio::ip::tcp::endpoint& endpoint);
    void send(const uint8_t* data, size_t size);
    void disconnect();
    bool isConnected() const { return m_connection->isOpen(); }

   private:
    void onReceived(int id, const uint8_t* data, size_t size) override;
    void onConnectionClosed(int id) override;

    boost::asio::io_context m_ioContext;
    std::thread m_thread;
    std::shared_ptr<TcpConnection> m_connection;
    Observer m_observer;
};

#endif
