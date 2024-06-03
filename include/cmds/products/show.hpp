#pragma once

#include "../command.hpp"

namespace cmds::products {

/**
 * @brief Command to show information about products in the system.
 *
 * This class provides a command to display information about products, either all products or a specific product based on the provided UID.
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
        "Displays information for products or a specific product with the specified product UID."
    ) {}

    /**
     * @brief Executes the Show command.
     *
     * This function executes the Show command to display information about products based on the provided arguments.
     *
     * @param args The arguments for the command.
     * @return The status code after execution (e.g., SUCCESS, FAIL).
     */
    int execute(utils::Args args) override;

    /**
     * @brief Displays detailed information about a product vertically.
     *
     * This static function displays detailed information about a given product in a vertical format.
     *
     * @param p The product to display.
     */
    static void display_product_vertical(shared_ptr<pharmacy::Product> p);

    /**
     * @brief Displays the header for product information in a horizontal format.
     *
     * This static function displays the header for product information in a horizontal format.
     */
    static void display_header_horizontal();

    /**
     * @brief Displays detailed information about a product horizontally.
     *
     * This static function displays detailed information about a given product in a horizontal format.
     *
     * @param p The product to display.
     */
    static void display_product_horizontal(shared_ptr<pharmacy::Product> p);
};

}
