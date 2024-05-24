#pragma once

#include "../command.h"

namespace cmds::reservations {

class Find : public Command {
public:
    Find() : Command(
        "Find",
        { "find" },
        "uid=[value] productUID=[value] quantity=[value] name=[value]",
        "Finds reservations in the system with the specified uid, product UID, quantity and/or name."
    ) {}

    int execute(utils::Args args) override;
};

}