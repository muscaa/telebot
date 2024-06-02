#pragma once

#include "../utils_base.h"

#define byte utils::_Byte

namespace utils {

typedef unsigned char _Byte;

/**
 * @brief Converts a boolean value to bytes (big endian).
 *
 * This function converts a boolean value to its byte representation in big endian order.
 *
 * @param v The boolean value to convert.
 * @param out The output function that handles each byte.
 */
void bool_to_bytes(bool v, function<void(byte)> out);

/**
 * @brief Converts a byte value to bytes (big endian).
 *
 * This function converts a byte value to its byte representation in big endian order.
 *
 * @param v The byte value to convert.
 * @param out The output function that handles each byte.
 */
void byte_to_bytes(byte v, function<void(byte)> out);

/**
 * @brief Converts a char value to bytes (big endian).
 *
 * This function converts a char value to its byte representation in big endian order.
 *
 * @param v The char value to convert.
 * @param out The output function that handles each byte.
 */
void char_to_bytes(char v, function<void(byte)> out);

/**
 * @brief Converts an int value to bytes (big endian).
 *
 * This function converts an int value to its byte representation in big endian order.
 *
 * @param v The int value to convert.
 * @param out The output function that handles each byte.
 */
void int_to_bytes(int v, function<void(byte)> out);

/**
 * @brief Converts a long value to bytes (big endian).
 *
 * This function converts a long value to its byte representation in big endian order.
 *
 * @param v The long value to convert.
 * @param out The output function that handles each byte.
 */
void long_to_bytes(long v, function<void(byte)> out);

/**
 * @brief Converts a float value to bytes (big endian).
 *
 * This function converts a float value to its byte representation in big endian order.
 *
 * @param v The float value to convert.
 * @param out The output function that handles each byte.
 */
void float_to_bytes(float v, function<void(byte)> out);

/**
 * @brief Converts a double value to bytes (big endian).
 *
 * This function converts a double value to its byte representation in big endian order.
 *
 * @param v The double value to convert.
 * @param out The output function that handles each byte.
 */
void double_to_bytes(double v, function<void(byte)> out);

/**
 * @brief Converts bytes (big endian) to a boolean value.
 *
 * This function converts bytes in big endian order to a boolean value.
 *
 * @param in The input function that provides each byte.
 * @return The converted boolean value.
 */
bool bytes_to_bool(function<byte()> in);

/**
 * @brief Converts bytes (big endian) to a byte value.
 *
 * This function converts bytes in big endian order to a byte value.
 *
 * @param in The input function that provides each byte.
 * @return The converted byte value.
 */
byte bytes_to_byte(function<byte()> in);

/**
 * @brief Converts bytes (big endian) to a char value.
 *
 * This function converts bytes in big endian order to a char value.
 *
 * @param in The input function that provides each byte.
 * @return The converted char value.
 */
char bytes_to_char(function<byte()> in);

/**
 * @brief Converts bytes (big endian) to an int value.
 *
 * This function converts bytes in big endian order to an int value.
 *
 * @param in The input function that provides each byte.
 * @return The converted int value.
 */
int bytes_to_int(function<byte()> in);

/**
 * @brief Converts bytes (big endian) to a long value.
 *
 * This function converts bytes in big endian order to a long value.
 *
 * @param in The input function that provides each byte.
 * @return The converted long value.
 */
long bytes_to_long(function<byte()> in);

/**
 * @brief Converts bytes (big endian) to a float value.
 *
 * This function converts bytes in big endian order to a float value.
 *
 * @param in The input function that provides each byte.
 * @return The converted float value.
 */
float bytes_to_float(function<byte()> in);

/**
 * @brief Converts bytes (big endian) to a double value.
 *
 * This function converts bytes in big endian order to a double value.
 *
 * @param in The input function that provides each byte.
 * @return The converted double value.
 */
double bytes_to_double(function<byte()> in);

}
