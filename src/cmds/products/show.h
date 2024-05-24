#pragma once

#include "../command.h"

namespace cmds::products {

class Show : public Command {
public:
    Show() : Command(
        "Show",
        { "show" },
        "[uid]",
        "Displays information for products or a specific product with the specified product UID."
    ) {}

    int execute(utils::Args args) override;

    static void display_product_vertical(shared_ptr<pharmacy::Product> p);

    static void display_header_horizontal();

    static void display_product_horizontal(shared_ptr<pharmacy::Product> p);
};

}