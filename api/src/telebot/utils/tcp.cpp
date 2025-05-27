#include "telebot/utils/tcp.h"

namespace telebot::utils::tcp {

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

    /*auto self{shared_from_this()};
    m_socket.async_read_some(buffers, [this, self](const auto &error, auto bytesTransferred) {
        if (error) {
            std::cerr << "TcpConnection::doRead() error: " + error.message() + ".\n";
            return close();
        }
        m_readBuffer.commit(bytesTransferred);
        m_observer.onReceived(m_id, static_cast<const uint8_t*>(m_readBuffer.data().data()), bytesTransferred);
        m_readBuffer.consume(bytesTransferred);
        doRead();
    });*/
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

    /*m_isWritting = true;
    auto self{shared_from_this()};
    m_socket.async_write_some(
        m_writeBuffer.data(),
        [this, self](const auto &error, auto bytesTransferred) {
            if (error) {
                std::cerr << "TcpConnection::doWrite() error: " + error.message() + ".\n";
                return close();
            }
            std::lock_guard<std::mutex> guard{m_writeBufferMutex};
            m_writeBuffer.consume(bytesTransferred);
            if (m_writeBuffer.size() == 0) {
                m_isWritting = false;
                return;
            }
            doWrite();
        });*/
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

} // namespace telebot::utils::tcp