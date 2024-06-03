#pragma once

#include "../command.hpp"

namespace cmds::reservations {

/**
 * @brief Command to add a reservation to the system.
 *
 * This class provides a command to add a reservation to the system with the specified product UID, quantity, and name.
 */
class Add : public Command {
public:
    /**
     * @brief Constructs an Add command object.
     *
     * This constructor initializes the Add command with its name, aliases, usage information, and description.
     */
    Add() : Command(
        "Add",
        { "add" },
        "<productUID> <quantity> <name>",
        "Adds a reservation to the system with the specified product UID, quantity and name."
    ) {}

    /**
     * @brief Executes the Add command.
     *
     * This function executes the Add command to add a reservation to the system based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;
};

}
