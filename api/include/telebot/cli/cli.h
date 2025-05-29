#pragma once

#include <string>
#include <vector>

#include "telebot/api.h"

namespace telebot::cli {

extern API std::vector<std::string> args;

int main_cli(int argc, char** argv);

} // namespace telebot::cli
