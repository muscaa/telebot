#pragma once

#include "../utils_base.hpp"
#include "../types/byte.hpp"

namespace utils {

/**
 * @brief Generates a random integer within a specified range.
 *
 * This function generates a random integer between the given minimum and maximum values (inclusive).
 *
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return A random integer between min and max (inclusive).
 */
int random_int(int min, int max);

/**
 * @brief Fills a buffer with random bytes.
 *
 * This function generates random bytes and fills the provided buffer with them.
 *
 * @param buf The buffer to be filled with random bytes.
 * @param len The length of the buffer.
 */
void random_bytes(byte* buf, int len);

}
