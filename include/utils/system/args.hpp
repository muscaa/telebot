#pragma once

#include "../utils_base.hpp"

namespace utils {

/**
 * @brief Class to handle command-line arguments.
 *
 * This class provides methods to access and manipulate command-line arguments.
 */
class Args {
private:
    vector<string> argsArray;
    int currentIndex;

public:
    /**
     * @brief Constructs an Args object.
     *
     * This constructor initializes the Args object with a vector of command-line arguments.
     *
     * @param argsArray The vector of command-line arguments.
     */
    Args(vector<string> argsArray);

    /**
     * @brief Accesses an argument by index.
     *
     * This operator overload allows accessing a command-line argument by its index.
     *
     * @param index The index of the argument to access.
     * @return The argument at the specified index.
     */
    string operator[](int index);

    /**
     * @brief Gets the number of command-line arguments.
     *
     * This function returns the number of command-line arguments.
     *
     * @return The number of command-line arguments.
     */
    int size();

    /**
     * @brief Gets the number of remaining arguments.
     *
     * This function returns the number of arguments that have not yet been processed.
     *
     * @return The number of remaining arguments.
     */
    int remaining();

    /**
     * @brief Gets the current argument index.
     *
     * This function returns the index of the current argument being processed.
     *
     * @return The current argument index.
     */
    int current();

    /**
     * @brief Checks if there are more arguments to process.
     *
     * This function checks if there are more arguments to process.
     *
     * @return True if there are more arguments to process, false otherwise.
     */
    bool hasNext();

    /**
     * @brief Converts the current argument to a string.
     *
     * This function converts the current argument to a string.
     *
     * @return The current argument as a string.
     */
    string String();

    /**
     * @brief Converts the current argument to an integer.
     *
     * This function converts the current argument to an integer.
     *
     * @return The current argument as an integer.
     */
    int Int();
};

/**
 * @brief Parses command-line arguments.
 *
 * This function parses command-line arguments and returns an Args object.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return An Args object containing the parsed command-line arguments.
 */
Args args(int argc, char* argv[]);

}
