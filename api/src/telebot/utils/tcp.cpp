#include "telebot/utils/tcp.h"

namespace telebot::utils::tcp {

// connection

void Connection::doRead() {
    isReading = true;

    boost::asio::mutable_buffer buffers(readBuffer.prepare(1024));

    socket->async_read_some(buffers, [this](const auto& error, auto bytesTransferred) {
        if (error) {
            close();
            return;
        }

        readBuffer.commit(bytesTransferred);
        listener->onReceived(id, static_cast<const uint8_t*>(readBuffer.data().data()), bytesTransferred);
        readBuffer.consume(bytesTransferred);

        doRead();
    });
}

void Connection::doWrite() {
    isWritting = true;

    socket->async_write_some(writeBuffer.data(), [this](const auto& error, auto bytesTransferred) {
        if (error) {
            close();
            return;
        }

        std::lock_guard<std::mutex> guard(writeBufferMutex);
        writeBuffer.consume(bytesTransferred);
        if (writeBuffer.size() == 0) {
            isWritting = false;
            return;
        }

        doWrite();
    });
}

void Connection::startReading() {
    if (!isReading) {
        doRead();
    }
}

void Connection::send(const uint8_t* data, size_t size) {
    std::lock_guard<std::mutex> guard(writeBufferMutex);
    
    std::ostream bufferStream(&writeBuffer);
    bufferStream.write(reinterpret_cast<const char*>(data), size);

    if (!isWritting) {
        doWrite();
    }
}

void Connection::close() {
    try {
        socket->cancel();
        socket->close();
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

void Client::connect(const boost::asio::ip::tcp::endpoint& endpoint) {
    if (connection) {
        return;
    }

    connecting = true;
    std::shared_ptr<boost::asio::ip::tcp::socket> socket = std::make_shared<boost::asio::ip::tcp::socket>(ioContext);
    socket->async_connect(endpoint, [this, socket](const auto& error) {
        if (error) {
            connecting = false;
            listener->onDisconnected(this);
            return;
        }

        connection = std::make_shared<Connection>(socket, this);
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
    if (isClosing) {
        return;
    }

    if (connections.erase(id) > 0) {
        listener->onConnectionClosed(this, id);
    }
}

void Server::doAccept() {
    isAccepting = true;
    acceptor.async_accept([this](const auto& error, auto socket) {
        if (error) {
            isAccepting = false;
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
    if (!isAccepting) {
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
    isClosing = true;
    acceptor.cancel();
    for (const auto& [id, connection] : connections) {
        connection->close();
    }
    connections.clear();
    isClosing = false;
}

} // namespace telebot::utils::tcp