#pragma once

#include <string>
#include <format>

namespace telebot::utils::logging {

void log(const std::string& prefix, const std::string& message);

template <class... Args>
void debug(const std::format_string<Args...> message, Args&&... args) {
    log("[DEBUG] ", std::format(message, std::forward<Args>(args)...));
}

template <class... Args>
void info(const std::format_string<Args...> message, Args&&... args) {
    log("[INFO] ", std::format(message, std::forward<Args>(args)...));
}

template <class... Args>
void warn(const std::format_string<Args...> message, Args&&... args) {
    log("[WARN] ", std::format(message, std::forward<Args>(args)...));
}

template <class... Args>
void error(const std::format_string<Args...> message, Args&&... args) {
    log("[ERROR] ", std::format(message, std::forward<Args>(args)...));
}

template <class... Args>
void critical(const std::format_string<Args...> message, Args&&... args) {
    log("[CRITICAL] ", std::format(message, std::forward<Args>(args)...));
}

} // namespace telebot::utils::logging
