#pragma once

#include "../command.h"

namespace cmds::reservations {

class Remove : public Command {
public:
    Remove() : Command(
        "Remove",
        { "remove", "rem" },
        "<uid...>",
        "Removes a reservation or more from the system with the specified reservation UID."
    ) {}

    int execute(utils::Args args) override;
};

}