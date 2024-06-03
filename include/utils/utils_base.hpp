#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdarg>
#include <filesystem>
#include <sstream>
#include <functional>

using namespace std;

namespace utils {

/**
 * @brief Converts a string to lowercase.
 *
 * This function takes a string and converts all of its characters to lowercase.
 *
 * @param s The input string to be converted to lowercase.
 * @return A new string with all characters in lowercase.
 */
string lower(string s);

}
