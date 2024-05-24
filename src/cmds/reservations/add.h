#pragma once

#include "../command.h"

namespace cmds::reservations {

class Add : public Command {
public:
    Add() : Command(
        "Add",
        { "add" },
        "<productUID> <quantity> <name>",
        "Adds a reservation to the system with the specified product UID, quantity and name."
    ) {}

    int execute(utils::Args args) override;
};

}