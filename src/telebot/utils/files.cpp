#include "telebot/utils/files.h"

#include <boost/dll.hpp>

namespace telebot::utils::files {

const boost::filesystem::path ROOT_DIR = boost::dll::program_location().parent_path();
const boost::filesystem::path PLUGINS_DIR = ROOT_DIR / "plugins";

void init() {
    boost::filesystem::create_directories(PLUGINS_DIR);
}

} // namespace telebot::utils::files
