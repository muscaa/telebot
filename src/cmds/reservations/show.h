#pragma once

#include "../command.h"

namespace cmds::reservations {

class Show : public Command {
public:
    Show() : Command("Show", { "show" }, "[name|id]", "Reservations show command.") {}

    int execute(utils::Args args) override;
};

}