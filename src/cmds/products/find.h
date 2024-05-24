#pragma once

#include "../command.h"

namespace cmds::products {

class Find : public Command {
public:
    Find() : Command(
        "Find",
        { "find" },
        "uid=[value] name=[value] type=[value] location=[value] quantity=[value]",
        "Finds products in the system with the specified uid, name, type, location and/or quantity."
    ) {}

    int execute(utils::Args args) override;
};

}