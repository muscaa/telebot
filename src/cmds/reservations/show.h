#pragma once

#include "../command.h"

namespace cmds::reservations {

/**
 * @brief Command to show information about reservations in the system.
 *
 * This class provides a command to display information about reservations, either all reservations or a specific reservation based on the provided UID.
 */
class Show : public Command {
public:
    /**
     * @brief Constructs a Show command object.
     *
     * This constructor initializes the Show command with its name, aliases, usage information, and description.
     */
    Show() : Command(
        "Show",
        { "show" },
        "[uid]",
        "Displays information for reservations or a specific reservation with the specified reservation UID."
    ) {}

    /**
     * @brief Executes the Show command.
     *
     * This function executes the Show command to display information about reservations based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;

    /**
     * @brief Displays detailed information about a reservation vertically.
     *
     * This static function displays detailed information about a given reservation in a vertical format.
     *
     * @param r The reservation to display.
     */
    static void display_reservation_vertical(shared_ptr<pharmacy::Reservation> r);

    /**
     * @brief Displays the header for reservation information in a horizontal format.
     *
     * This static function displays the header for reservation information in a horizontal format.
     */
    static void display_header_horizontal();

    /**
     * @brief Displays detailed information about a reservation horizontally.
     *
     * This static function displays detailed information about a given reservation in a horizontal format.
     *
     * @param r The reservation to display.
     */
    static void display_reservation_horizontal(shared_ptr<pharmacy::Reservation> r);
};

}
