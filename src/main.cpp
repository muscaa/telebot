#include "telebot/telebot.h"

#include <boost/dll.hpp>
#include <boost/function.hpp>
#include <iostream>

int main(int argc, char **argv) {
    if (!telebot::init()) {
        SDL_Log("Error: telebot::init() failed\n");
        return -1;
    }

    try {
        boost::dll::shared_library lib("my_plugin.dll");
        boost::function<void()> plugin_main = lib.get<void()>("plugin_main");
        plugin_main();
    } catch (const std::exception& e) {
        std::cout << "Failed to load plugin: " << e.what() << std::endl;
    }

    telebot::run();
    telebot::dispose();

    return 0;
}
