#include "telebot/utils/tcp.h"

#include "telebot/utils/logging.h"

namespace telebot::utils::tcp {

namespace log = telebot::utils::logging;

// connection

void Connection::doRead() {
    reading = true;

    boost::asio::mutable_buffer buffers(readBuffer.prepare(1024));
    socket.async_read_some(buffers, [this](const boost::system::error_code& error, std::size_t length) {
        if (error) {
            close();
            return;
        }

        readBuffer.commit(length);
        listener->onReceived(id, static_cast<const uint8_t*>(readBuffer.data().data()), length);
        readBuffer.consume(length);

        doRead();
    });
}

void Connection::doWrite() {
    writing = true;

    socket.async_write_some(writeBuffer.data(), [this](const boost::system::error_code& error, std::size_t length) {
        if (error) {
            close();
            return;
        }

        std::lock_guard<std::mutex> guard(writeBufferMutex);
        writeBuffer.consume(length);
        if (writeBuffer.size() == 0) {
            writing = false;
            return;
        }

        doWrite();
    });
}

void Connection::startReading() {
    if (!reading) {
        doRead();
    }
}

void Connection::send(const uint8_t* data, size_t size) {
    std::lock_guard<std::mutex> guard(writeBufferMutex);
    
    std::ostream bufferStream(&writeBuffer);
    bufferStream.write(reinterpret_cast<const char*>(data), size);

    if (!writing) {
        doWrite();
    }
}

void Connection::close() {
    try {
        socket.cancel();
        socket.close();
    } catch (const std::exception& e) {
        return;
    }

    listener->onConnectionClosed(id);
}

// client

void Client::onReceived(int id, const uint8_t* data, size_t size) {
    listener->onReceived(this, data, size);
}

void Client::onConnectionClosed(int id) {
    if (connection) {
        connection.reset();
        listener->onDisconnected(this);
    }
}

void Client::connect(const boost::asio::ip::address& address, boost::asio::ip::port_type port) {
    if (connection) {
        return;
    }

    connecting = true;
    boost::asio::ip::tcp::socket socket(ioContext);
    connection = std::make_shared<Connection>(socket, this);
    connection->getSocket().async_connect(boost::asio::ip::tcp::endpoint(address, port), [this](const boost::system::error_code& error) {
        if (error) {
            connecting = false;
            listener->onDisconnected(this);
            return;
        }

        connection->startReading();
        connecting = false;
        listener->onConnected(this);
    });
}

void Client::send(const uint8_t* data, size_t size) {
    if (connection) {
        connection->send(data, size);
    }
}

void Client::disconnect() {
    if (connection) {
        connection->close();
    }
}

// server

void Server::onReceived(int id, const uint8_t* data, size_t size) {
    listener->onReceived(this, id, data, size);
}

void Server::onConnectionClosed(int id) {
    if (closing) {
        return;
    }

    if (connections.erase(id) > 0) {
        listener->onConnectionClosed(this, id);
    }
}

void Server::doAccept() {
    accepting = true;

    acceptor.async_accept([this](const boost::system::error_code& error, boost::asio::ip::tcp::socket socket) {
        if (error) {
            accepting = false;
            return;
        }

        std::shared_ptr<Connection> connection = std::make_shared<Connection>(socket, this, connectionIdCounter);
        connection->startReading();
        connections[connectionIdCounter] = connection;
        listener->onConnectionAccepted(this, connectionIdCounter);
        connectionIdCounter++;

        doAccept();
    });
}

bool Server::listen(const boost::asio::ip::tcp& protocol, uint16_t port) {
    try {
        acceptor.open(protocol);
        acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor.bind(boost::asio::ip::tcp::endpoint(protocol, port));
        acceptor.listen(boost::asio::socket_base::max_listen_connections);
    } catch (const std::exception& e) {
        return false;
    }
    return true;
}

void Server::startAccepting() {
    if (!accepting) {
        doAccept();
    }
}

void Server::send(int id, const uint8_t* data, size_t size) {
    if (connections.count(id) == 0) {
        return;
    }

    connections.at(id)->send(data, size);
}

void Server::sendAll(const uint8_t* data, size_t size) {
    for (const auto& [id, connection] : connections) {
        connection->send(data, size);
    }
}

void Server::close() {
    closing = true;
    acceptor.cancel();
    for (const auto& [id, connection] : connections) {
        connection->close();
    }
    connections.clear();
    closing = false;
}

} // namespace telebot::utils::tcp