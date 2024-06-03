#pragma once

#include "../command.hpp"

namespace cmds::reservations {

/**
 * @brief Command to remove reservations from the system.
 *
 * This class provides a command to remove reservations from the system based on their unique identifiers (UIDs).
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
        "Removes a reservation or more from the system with the specified reservation UID."
    ) {}

    /**
     * @brief Executes the Remove command.
     *
     * This function executes the Remove command to remove reservations from the system based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;
};

}
