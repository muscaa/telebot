#include "telebot/utils/socket.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

namespace telebot::utils {

void start_server() {
    boost::asio::io_context io;
    udp::socket socket(io, udp::endpoint(udp::v4(), 8080));

    char buffer[1024];
    udp::endpoint client_endpoint;
    
    while (true) {
        size_t len = socket.receive_from(boost::asio::buffer(buffer), client_endpoint);
        std::cout << "Received: " << std::string(buffer, len) << std::endl;

        socket.send_to(boost::asio::buffer(buffer, len), client_endpoint);
    }
}

void start_client() {
    boost::asio::io_context io;
    udp::socket socket(io);
    socket.open(udp::v4());

    udp::endpoint server_endpoint(boost::asio::ip::make_address("127.0.0.1"), 8080);
    std::string message = "Hello, Server!";
    
    socket.send_to(boost::asio::buffer(message), server_endpoint);

    char buffer[1024];
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);

    std::cout << "Server Response: " << std::string(buffer, len) << std::endl;
}

}  // namespace telebot::utils
