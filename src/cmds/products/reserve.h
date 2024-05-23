#pragma once

#include "../command.h"

namespace cmds::products {

class Reserve : public Command {
public:
    Reserve() : Command("Reserve", { "reserve" }, "<id> <quantity> <name>", "Products reserve command.") {}

    int execute(utils::Args args) override;
};

}