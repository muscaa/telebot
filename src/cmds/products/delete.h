#pragma once

#include "../command.h"

namespace cmds::products {

class Delete : public Command {
public:
    Delete() : Command("Delete", { "delete" }, "<id>", "Products delete command.") {}

    int execute(utils::Args args) override;
};

}