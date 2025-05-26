#include "TcpServer.hpp"

#include <iostream>
#include <string>

void TcpServer::Observer::onConnectionAccepted(TcpServer* server, [[maybe_unused]] int connectionId) {}

void TcpServer::Observer::onReceived(TcpServer* server,
                                     [[maybe_unused]] int connectionId,
                                     [[maybe_unused]] const uint8_t* data,
                                     [[maybe_unused]] const size_t size) {}

void TcpServer::Observer::onConnectionClosed(TcpServer* server, [[maybe_unused]] int connectionId) {}

TcpServer::TcpServer(Observer* observer)
    : m_ioContext(),
      m_thread([this]() { m_ioContext.run(); }),
      m_acceptor(m_ioContext),
      m_connections{},
      m_observer{observer},
      m_connectionCount{0},
      m_isAccepting{false},
      m_isClosing{false} {}

bool TcpServer::listen(const boost::asio::ip::tcp &protocol, uint16_t port) {
    try {
        m_acceptor.open(protocol);
        m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        m_acceptor.bind({protocol, port});
        m_acceptor.listen(boost::asio::socket_base::max_listen_connections);
    } catch (const std::exception &e) {
        std::cerr << "TcpServer::listen() exception: " + static_cast<std::string>(e.what()) + ".\n";
        return false;
    }
    return true;
}

void TcpServer::startAcceptingConnections() {
    if (!m_isAccepting) {
        doAccept();
    }
}

void TcpServer::send(int connectionId, const uint8_t* data, size_t size) {
    if (m_connections.count(connectionId) == 0) {
        std::cerr << "TcpServer::send() error: connection not found.\n";
        return;
    }
    m_connections.at(connectionId)->send(data, size);
}

void TcpServer::sendAll(const uint8_t* data, size_t size) {
    for (const auto& [id, connection] : m_connections) {
        connection->send(data, size);
    }
}

void TcpServer::close() {
    m_isClosing = true;
    m_acceptor.cancel();
    for (const auto &connection : m_connections) {
        connection.second->close();
    }
    m_connections.clear();
    m_isClosing = false;
    std::cout << "TCPServer disconnected.\n";
}

void TcpServer::doAccept() {
    m_isAccepting = true;
    m_acceptor.async_accept([this](const auto &error, auto socket) {
        if (error) {
            std::cerr << "TcpServer::doAccept() error: " + error.message() + ".\n";
            m_isAccepting = false;
            return;
        } else {
            auto connection{TcpConnection::create(std::move(socket), *this, m_connectionCount)};
            connection->startReading();
            m_connections.insert({m_connectionCount, std::move(connection)});
            std::cout << "TCPServer accepted connection.\n";
            m_observer->onConnectionAccepted(this, m_connectionCount);
            m_connectionCount++;
        }
        doAccept();
    });
}

void TcpServer::onReceived(int connectionId, const uint8_t* data, size_t size) {
    m_observer->onReceived(this, connectionId, data, size);
}

void TcpServer::onConnectionClosed(int connectionId) {
    if (m_isClosing) {
        return;
    }
    if (m_connections.erase(connectionId) > 0) {
        std::cout << "TCPServer removed connection.\n";
        m_observer->onConnectionClosed(this, connectionId);
    }
}
