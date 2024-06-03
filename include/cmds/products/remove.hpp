#pragma once

#include "../command.hpp"

namespace cmds::products {

/**
 * @brief Command to remove products from the system.
 *
 * This class provides a command to remove products from the system based on their unique identifiers (UIDs).
 */
class Remove : public Command {
public:
    /**
     * @brief Constructs a Remove command object.
     *
     * This constructor initializes the Remove command with its name, aliases, usage information, and description.
     */
    Remove() : Command(
        "Remove",
        { "remove", "rem" },
        "<uid...>",
        "Removes a product or more from the system with the specified product UID."
    ) {}

    /**
     * @brief Executes the Remove command.
     *
     * This function executes the Remove command to remove products from the system based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;
};

}
