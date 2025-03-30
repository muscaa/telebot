#include "telebot.h"

int main(int argc, char **argv) {
    if (!TeleBot::Init()) {
        SDL_Log("Error: telebot::init() failed\n");
        return -1;
    }

    TeleBot::Render();
    TeleBot::Dispose();

    return 0;
}
