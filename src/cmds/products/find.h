#pragma once

#include "../command.h"

namespace cmds::products {

/**
 * @brief Command to find products in the system.
 *
 * This class provides a command to find products in the system based on specified criteria such as uid, name, type, location, and/or quantity.
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
        "uid=[value] name=[value] type=[value] location=[value] quantity=[value]",
        "Finds products in the system with the specified uid, name, type, location and/or quantity."
    ) {}

    /**
     * @brief Executes the Find command.
     *
     * This function executes the Find command to find products in the system based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;
};

}
