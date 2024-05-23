#include "show.h"

int cmds::products::Show::execute(utils::Args args) {
    if (args.remaining() > 1) return HELP;
    if (args.remaining() == 1) {
        string id = args.String();
        int index = pharmacy::find_product(id);
        if (index == -1) {
            cout << "Product with ID " << id << " does not exist." << endl;
            return FAIL;
        }

        shared_ptr<pharmacy::Product> p = pharmacy::products[index];
        cout << "Product ID: " << p->getID() << endl;
        cout << "Product type: " << p->getType() << endl;
        cout << "Product location: " << p->getLocation() << endl;
        cout << "Product quantity: " << p->getQuantity() << endl;
        cout << "Product available quantity: " << p->getAvailableQuantity() << endl;
        return SUCCESS;
    }

    print_left(30, "ID");
    print_middle(30, "Type");
    print_middle(40, "Location");
    print_right(20, "Quantity");
    cout << endl;
    cout << string(120, '-') << endl;

    for (shared_ptr<pharmacy::Product>& p : pharmacy::products) {
        print_left(30, p->getID());
        print_middle(30, p->getType());
        print_middle(40, p->getLocation());
        print_right(20, p->getQuantity());
        cout << endl;
    }

    return SUCCESS;
}
