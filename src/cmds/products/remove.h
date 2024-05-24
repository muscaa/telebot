#pragma once

#include "../command.h"

namespace cmds::products {

class Remove : public Command {
public:
    Remove() : Command(
        "Remove",
        { "remove", "rem" },
        "<uid...>",
        "Removes a product or more from the system with the specified product UID."
    ) {}

    int execute(utils::Args args) override;
};

}