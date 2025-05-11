#include "telebot/utils/files.h"

#include <boost/dll.hpp>

namespace telebot::utils::files {

const boost::filesystem::path ROOT_DIR = boost::dll::program_location().parent_path();
const boost::filesystem::path PLUGINS_DIR = dir(ROOT_DIR / "plugins");
const boost::filesystem::path TEMP_DIR = dir(ROOT_DIR / "temp");

void init() {
}

const boost::filesystem::path& dir(const boost::filesystem::path& path) {
    boost::filesystem::create_directories(path);
    return path;
}

} // namespace telebot::utils::files
