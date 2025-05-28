#include "telebot/cli/cli.h"

#include <boost/function.hpp>

#include "telebot/utils/logging.h"
#include "telebot/utils/files.h"
#include "telebot/utils/platform.h"
#include "telebot/plugins.h"

namespace telebot::cli {

namespace log = telebot::utils::logging;

std::vector<std::string> args;

int main_cli(int argc, char** argv) {
    args = std::vector<std::string>(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }
    
    if (args.size() < 2) {
        log::info("Usage: {} <plugin-id> [args...]", args[0]);
        return 1;
    }

    telebot::utils::files::init();
    telebot::utils::platform::init();
    telebot::plugins::load_cli_from(telebot::utils::files::PLUGINS_DIR);

    telebot::plugins::Plugin* plugin = telebot::plugins::loaded_plugins[args[1]];
    boost::function<int (const telebot::plugins::Plugin&)> main_cli = plugin->getLib()->get_function<int (const telebot::plugins::Plugin&)>(plugin->getPluginMainCli());
    return main_cli(*plugin);
}

} // namespace telebot::cli
