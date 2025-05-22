#include "telebot/cli/cli.h"

#include "telebot/utils/logging.h"

namespace telebot::cli {

namespace log = telebot::utils::logging;

int main(const std::vector<std::string>& args) {
    log::info("telebot::cli::main() called with {} arguments", args.size());
    return 0;
}

} // namespace telebot::cli
