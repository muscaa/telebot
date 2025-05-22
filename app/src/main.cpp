#include "telebot/telebot.h"

int main(int argc, char** argv) {
    if (!telebot::init()) {
        SDL_Log("Error: telebot::init() failed\n");
        return -1;
    }

    telebot::run();
    telebot::dispose();

    return 0;
}
