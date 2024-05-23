#pragma once

#include "../command.h"

namespace cmds::reservations {

class Cancel : public Command {
public:
    Cancel() : Command("Cancel", { "cancel" }, "<id>", "Reservations cancel command.") {}

    int execute(utils::Args args) override;
};

}