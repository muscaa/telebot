#pragma once

#include "../command.hpp"

namespace cmds::products {

/**
 * @brief Command to add a product to the system.
 *
 * This class provides a command to add a product to the system with the specified name, type, location, and quantity.
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
        "<name> <type> <location> <quantity>",
        "Adds a product to the system with the specified name, type, location and quantity."
    ) {}

    /**
     * @brief Executes the Add command.
     *
     * This function executes the Add command to add a product to the system based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;
};

}
