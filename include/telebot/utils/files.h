#pragma once

#include <boost/filesystem.hpp>

namespace telebot::utils::files {

extern const boost::filesystem::path ROOT_DIR;
extern const boost::filesystem::path PLUGINS_DIR;
extern const boost::filesystem::path TEMP_DIR;

void init();

const boost::filesystem::path& dir(const boost::filesystem::path& path);

} // namespace telebot::utils::files
