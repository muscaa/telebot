#include "telebot/cli/cli.h"

int main(int argc, char** argv) {
    std::vector<std::string> args(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }

    return telebot::cli::main(args);
}
