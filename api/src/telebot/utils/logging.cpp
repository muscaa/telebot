#include "telebot/utils/logging.h"

#include <iostream>

namespace telebot::utils::logging {

void log(const std::string& prefix, const std::string& message) {
    std::cout << prefix << message << std::endl;
}

} // namespace telebot::utils::logging
