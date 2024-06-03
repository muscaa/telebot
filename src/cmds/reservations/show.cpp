#include "cmds/reservations/show.hpp"

#include "cmds/products/show.hpp"

void cmds::reservations::Show::display_reservation_vertical(shared_ptr<pharmacy::Reservation> r) {
    cout << "Reservation UID: " << r->getUID() << endl;
    cout << "Reservation quantity: " << r->getQuantity() << endl;
    cout << "Reservation name: " << r->getName() << endl;

    cmds::products::Show::display_product_vertical(r->getProduct());
}

void cmds::reservations::Show::display_header_horizontal() {
    print_left(10, "UID");
    print_middle(10, "Quantity");
    print_middle(40, "Name");
    print_middle(30, "Product Name");
    print_right(10, "Product UID");
    cout << endl;
    cout << string(100, '-') << endl;
}

void cmds::reservations::Show::display_reservation_horizontal(shared_ptr<pharmacy::Reservation> r) {
    auto p = r->getProduct();

    print_left(10, r->getUID());
    print_middle(10, r->getQuantity());
    print_middle(40, r->getName());
    print_middle(30, p->getName());
    print_right(10, p->getUID());
    cout << endl;
}

int cmds::reservations::Show::execute(utils::Args args) {
    if (args.remaining() > 1) return HELP;
    if (args.remaining() == 1) {
        string uid = args.String();
        if (!pharmacy::reservation_exists(uid)) {
            cout << "Reservation with UID " << uid << " does not exist." << endl;
            return FAIL;
        }

        display_reservation_vertical(pharmacy::reservations[uid]);
        return SUCCESS;
    }

    display_header_horizontal();
    for (auto& pair : pharmacy::reservations) {
        auto r = pair.second;
        
        display_reservation_horizontal(r);
    }

    return SUCCESS;
}
