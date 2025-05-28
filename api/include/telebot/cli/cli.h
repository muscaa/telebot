#pragma once

#include <string>
#include <vector>

namespace telebot::cli {

extern std::vector<std::string> args;

int main_cli(int argc, char** argv);

} // namespace telebot::cli
