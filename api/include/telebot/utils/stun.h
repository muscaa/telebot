#pragma once

#include <string>
#include <TcpServer.hpp>
#include <TcpClient.hpp>

namespace telebot::utils::stun {

TcpServer* server(int port);

TcpClient* client(std::string address, int port, std::string name);

} // namespace telebot::utils::stun
