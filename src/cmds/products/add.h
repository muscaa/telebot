#pragma once

#include "../command.h"

namespace cmds::products {

class Add : public Command {
public:
    Add() : Command("Add", { "add" }, "<id> <type> <location> <quantity>", "Products add command.") {}

    int execute(utils::Args args) override;
};

}