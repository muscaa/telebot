#include "telebot/cli/cli.h"

#include "telebot/utils/logging.h"
#include "telebot/utils/stun.h"

namespace telebot::cli {

namespace log = telebot::utils::logging;

int main(const std::vector<std::string>& args) {
    log::info("telebot::cli::main() called with {} arguments", args.size());

    if (args.size() < 2) {
        log::info("Usage: {} <server|client>", args[0]);
        return 1;
    }

    if (args[1] == "server") {
        TcpServer* server = telebot::utils::stun::server(1234);

        while (server->isRunning()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else if (args[1] == "client") {
        TcpClient* client = telebot::utils::stun::client("127.0.0.1", 1234);

        while (client->isConnected()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    return 0;
}

} // namespace telebot::cli
