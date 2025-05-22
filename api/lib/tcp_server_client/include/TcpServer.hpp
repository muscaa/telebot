#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <unordered_map>

#include "TcpConnection.hpp"

class TcpServer : private TcpConnection::Observer {
   public:
    struct Observer {
        virtual void onConnectionAccepted(const TcpServer& server, int connectionId);
        virtual void onReceived(const TcpServer& server, int connectionId, const char* data, size_t size);
        virtual void onConnectionClosed(const TcpServer& server, int connectionId);
    };

    TcpServer(const Observer& observer);

    bool listen(const boost::asio::ip::tcp& protocol, uint16_t port);
    void startAcceptingConnections();
    void send(int connectionId, const char* data, size_t size);
    void close();
    bool isRunning() const { return m_acceptor.is_open(); }

   private:
    void doAccept();
    void onReceived(int connectionId, const char* data, size_t size) override;
    void onConnectionClosed(int connectionId) override;

    boost::asio::io_context m_ioContext;
    std::thread m_thread;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::unordered_map<int, std::shared_ptr<TcpConnection>> m_connections;
    Observer m_observer;
    int m_connectionCount;
    bool m_isAccepting;
    bool m_isClosing;
};

#endif
