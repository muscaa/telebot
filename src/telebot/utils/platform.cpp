#include "telebot/utils/platform.h"

namespace telebot::utils::platform {

static std::string get_system() {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        return WINDOWS;
    #elif __APPLE__
        return MACOS;
    #elif __linux__
        return LINUX;
    #else
        return UNKNOWN;
    #endif
}

static std::string get_arch() {
    #if defined(__x86_64__) || defined(_M_X64)
        return X64;
    #elif defined(__aarch64__) || defined(_M_ARM64)
        return ARM64;
    #endif
}

static std::string get_lib_ext() {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        return DLL;
    #elif __APPLE__
        return DYLIB;
    #elif __linux__
        return SO;
    #else
        return UNKNOWN;
    #endif
}

const std::string SYSTEM = get_system();
const std::string ARCH = get_arch();
const std::string LIB_EXT = get_lib_ext();

void init() {

}

} // namespace telebot::utils::platform
