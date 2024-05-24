#pragma once

#include "../command.h"

namespace cmds::products {

class Add : public Command {
public:
    Add() : Command(
        "Add",
        { "add" },
        "<name> <type> <location> <quantity>",
        "Adds a product to the system with the specified name, type, location and quantity."
    ) {}

    int execute(utils::Args args) override;
};

}