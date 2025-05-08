#pragma once

#include <boost/filesystem.hpp>

namespace telebot::utils::files {

extern const boost::filesystem::path ROOT_DIR;
extern const boost::filesystem::path PLUGINS_DIR;

void init();

} // namespace telebot::utils::files
