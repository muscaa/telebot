#include "show.h"

void cmds::products::Show::display_product_vertical(shared_ptr<pharmacy::Product> p) {
    cout << "Product UID: " << p->getUID() << endl;
    cout << "Product name: " << p->getName() << endl;
    cout << "Product type: " << p->getType() << endl;
    cout << "Product location: " << p->getLocation() << endl;
    cout << "Product quantity: " << p->getQuantity() << endl;
    cout << "Product available quantity: " << p->getAvailableQuantity() << endl;
}

void cmds::products::Show::display_header_horizontal() {
    print_left(10, "UID");
    print_middle(30, "Name");
    print_middle(30, "Type");
    print_middle(40, "Location");
    print_right(10, "Quantity");
    cout << endl;
    cout << string(120, '-') << endl;
}

void cmds::products::Show::display_product_horizontal(shared_ptr<pharmacy::Product> p) {
    print_left(10, p->getUID());
    print_middle(30, p->getName());
    print_middle(30, p->getType());
    print_middle(40, p->getLocation());
    print_right(10, p->getQuantity());
    cout << endl;
}

int cmds::products::Show::execute(utils::Args args) {
    if (args.remaining() > 1) return HELP;
    if (args.remaining() == 1) {
        string uid = args.String();
        if (!pharmacy::product_exists(uid)) {
            cout << "Product with UID " << uid << " does not exist." << endl;
            return FAIL;
        }

        display_product_vertical(pharmacy::products[uid]);
        return SUCCESS;
    }

    display_header_horizontal();
    for (auto& pair : pharmacy::products) {
        auto p = pair.second;

        display_product_horizontal(p);
    }

    return SUCCESS;
}
