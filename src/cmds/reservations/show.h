#pragma once

#include "../command.h"

namespace cmds::reservations {

class Show : public Command {
public:
    Show() : Command(
        "Show",
        { "show" },
        "[uid]",
        "Displays information for reservations or a specific reservation with the specified reservation UID."
    ) {}

    int execute(utils::Args args) override;

    static void display_reservation_vertical(shared_ptr<pharmacy::Reservation> r);

    static void display_header_horizontal();

    static void display_reservation_horizontal(shared_ptr<pharmacy::Reservation> r);
};

}