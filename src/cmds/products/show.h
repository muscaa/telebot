#pragma once

#include "../command.h"

namespace cmds::products {

class Show : public Command {
public:
    Show() : Command("Show", { "show" }, "[id]", "Products show command.") {}

    int execute(utils::Args args) override;
};

}