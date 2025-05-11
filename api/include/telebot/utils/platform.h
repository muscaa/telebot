#pragma once

#include <string>

namespace telebot::utils::platform {

const std::string UNKNOWN = "unknown";

// systems
const std::string WINDOWS = "windows";
const std::string LINUX = "linux";
const std::string MACOS = "macos";

// architectures
const std::string X64 = "x64";
const std::string ARM64 = "arm64";

// lib extenions
const std::string DLL = ".dll";
const std::string SO = ".so";
const std::string DYLIB = ".dylib";

extern const std::string SYSTEM;
extern const std::string ARCH;
extern const std::string LIB_EXT;

void init();

} // namespace telebot::utils::platform
