#pragma once

#include "../utils_base.h"
#include "../types/byte.h"

namespace utils {

/**
 * @brief Class for handling hash values.
 *
 * This class provides methods to create, manipulate, and compare hash values.
 */
class HASH {
private:
    int length; /**< Length of the hash */
    byte* data; /**< Data of the hash */

public:
    /**
     * @brief Constructs a HASH object with a specified length.
     *
     * This constructor initializes the HASH object with a specified length.
     *
     * @param length The length of the hash.
     */
    HASH(int length);

    /**
     * @brief Constructs a HASH object from a hexadecimal string.
     *
     * This constructor initializes the HASH object from a given hexadecimal string.
     *
     * @param hex The hexadecimal string representing the hash.
     */
    HASH(string hex);

    /**
     * @brief Default constructor for HASH.
     *
     * This constructor initializes an empty HASH object.
     */
    HASH();

    /**
     * @brief Destructor for HASH.
     *
     * This destructor cleans up the allocated resources.
     */
    ~HASH();

    /**
     * @brief Converts the hash to a hexadecimal string.
     *
     * This function converts the hash value to its hexadecimal string representation.
     *
     * @return The hexadecimal string representation of the hash.
     */
    string toHex();

    /**
     * @brief Compares two HASH objects for equality.
     *
     * This operator overload allows comparing two HASH objects for equality.
     *
     * @param other The other HASH object to compare with.
     * @return True if the hash values are equal, false otherwise.
     */
    bool operator==(HASH& other);

    /**
     * @brief Generates a random hash of a specified length.
     *
     * This static function generates a random hash with the given length.
     *
     * @param length The length of the random hash.
     * @return A random HASH object of the specified length.
     */
    static HASH random(int length);
};

/**
 * @brief Converts a buffer of bytes to a hexadecimal string.
 *
 * This function converts a buffer of bytes to its hexadecimal string representation.
 *
 * @param buf The buffer of bytes to convert.
 * @param len The length of the buffer.
 * @return The hexadecimal string representation of the buffer.
 */
string hex_string(byte* buf, int len);

/**
 * @brief Converts a hexadecimal string to a buffer of bytes.
 *
 * This function converts a hexadecimal string to its corresponding byte representation and fills the provided buffer.
 *
 * @param buf The buffer to be filled with the byte representation.
 * @param hex The hexadecimal string to convert.
 */
void hex_bytes(byte* buf, string hex);

}
