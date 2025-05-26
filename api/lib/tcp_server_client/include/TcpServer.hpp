#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <unordered_map>

#include "TcpConnection.hpp"

class TcpServer : private TcpConnection::Observer {
   public:
    struct Observer {
        virtual void onConnectionAccepted(TcpServer* server, int id);
        virtual void onReceived(TcpServer* server, int id, const uint8_t* data, size_t size);
        virtual void onConnectionClosed(TcpServer* server, int id);
    };

    TcpServer(Observer* observer);

    bool listen(const boost::asio::ip::tcp& protocol, uint16_t port);
    void startAcceptingConnections();
    void send(int id, const uint8_t* data, size_t size);
    void sendAll(const uint8_t* data, size_t size);
    void close();
    bool isRunning() const { return m_acceptor.is_open(); }
    std::unordered_map<int, std::shared_ptr<TcpConnection>>& getConnections() { return m_connections; }

   private:
    void doAccept();
    void onReceived(int id, const uint8_t* data, size_t size) override;
    void onConnectionClosed(int id) override;

    boost::asio::io_context m_ioContext;
    std::thread m_thread;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::unordered_map<int, std::shared_ptr<TcpConnection>> m_connections;
    Observer* m_observer;
    int m_connectionCount;
    bool m_isAccepting;
    bool m_isClosing;
};

#endif
