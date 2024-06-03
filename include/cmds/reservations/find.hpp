#pragma once

#include "../command.hpp"

namespace cmds::reservations {

/**
 * @brief Command to find reservations in the system.
 *
 * This class provides a command to find reservations in the system based on specified criteria such as uid, product UID, quantity, and/or name.
 */
class Find : public Command {
public:
    /**
     * @brief Constructs a Find command object.
     *
     * This constructor initializes the Find command with its name, aliases, usage information, and description.
     */
    Find() : Command(
        "Find",
        { "find" },
        "uid=[value] productUID=[value] quantity=[value] name=[value]",
        "Finds reservations in the system with the specified uid, product UID, quantity and/or name."
    ) {}

    /**
     * @brief Executes the Find command.
     *
     * This function executes the Find command to find reservations in the system based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;
};

}
