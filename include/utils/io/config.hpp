#pragma once

#include "../utils_base.hpp"
#include "../types/byte.hpp"

namespace utils {

/**
 * @brief Class for writing configuration data to a file.
 *
 * This class provides methods to write various data types to a configuration file.
 */
class ConfigWriter {
private:
    ofstream outStream;

public:
    /**
     * @brief Constructs a ConfigWriter object.
     *
     * This constructor initializes the ConfigWriter object and opens the specified file for writing.
     *
     * @param file The name of the file to write to.
     */
    ConfigWriter(string file);

    /**
     * @brief Writes a boolean value to the configuration file.
     *
     * @param value The boolean value to write.
     */
    void Bool(bool value);

    /**
     * @brief Writes a byte value to the configuration file.
     *
     * @param value The byte value to write.
     */
    void Byte(byte value);

    /**
     * @brief Writes a char value to the configuration file.
     *
     * @param value The char value to write.
     */
    void Char(char value);

    /**
     * @brief Writes an int value to the configuration file.
     *
     * @param value The int value to write.
     */
    void Int(int value);

    /**
     * @brief Writes a long value to the configuration file.
     *
     * @param value The long value to write.
     */
    void Long(long value);

    /**
     * @brief Writes a float value to the configuration file.
     *
     * @param value The float value to write.
     */
    void Float(float value);

    /**
     * @brief Writes a double value to the configuration file.
     *
     * @param value The double value to write.
     */
    void Double(double value);

    /**
     * @brief Writes a string of a specified length to the configuration file.
     *
     * @param value The string to write.
     * @param length The length of the string to write.
     */
    void String(string value, int length);

    /**
     * @brief Writes a length-prefixed string to the configuration file.
     *
     * @param value The string to write.
     */
    void LenString(string value);

    /**
     * @brief Writes a buffer of bytes to the configuration file.
     *
     * @param buf The buffer containing the bytes to write.
     * @param len The number of bytes to write.
     */
    void Bytes(byte* buf, int len);

    /**
     * @brief Flushes the output stream.
     *
     * This function flushes the output stream, ensuring all buffered data is written to the file.
     */
    void flush();

    /**
     * @brief Closes the output stream.
     *
     * This function closes the output stream.
     */
    void close();
};

/**
 * @brief Class for reading configuration data from a file.
 *
 * This class provides methods to read various data types from a configuration file.
 */
class ConfigReader {
private:
    ifstream inStream;

public:
    /**
     * @brief Constructs a ConfigReader object.
     *
     * This constructor initializes the ConfigReader object and opens the specified file for reading.
     *
     * @param file The name of the file to read from.
     */
    ConfigReader(string file);

    /**
     * @brief Reads a boolean value from the configuration file.
     *
     * @return The boolean value read.
     */
    bool Bool();

    /**
     * @brief Reads a byte value from the configuration file.
     *
     * @return The byte value read.
     */
    byte Byte();

    /**
     * @brief Reads a char value from the configuration file.
     *
     * @return The char value read.
     */
    char Char();

    /**
     * @brief Reads an int value from the configuration file.
     *
     * @return The int value read.
     */
    int Int();

    /**
     * @brief Reads a long value from the configuration file.
     *
     * @return The long value read.
     */
    long Long();

    /**
     * @brief Reads a float value from the configuration file.
     *
     * @return The float value read.
     */
    float Float();

    /**
     * @brief Reads a double value from the configuration file.
     *
     * @return The double value read.
     */
    double Double();

    /**
     * @brief Reads a string of a specified length from the configuration file.
     *
     * @param length The length of the string to read.
     * @return The string read.
     */
    string String(int length);

    /**
     * @brief Reads a length-prefixed string from the configuration file.
     *
     * @return The string read.
     */
    string LenString();

    /**
     * @brief Reads a buffer of bytes from the configuration file.
     *
     * @param buf The buffer to store the read bytes.
     * @param len The number of bytes to read.
     */
    void Bytes(byte* buf, int len);

    /**
     * @brief Closes the input stream.
     *
     * This function closes the input stream.
     */
    void close();
};

}
