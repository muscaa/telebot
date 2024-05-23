#include "add.h"

int cmds::products::Add::execute(utils::Args args) {
    if (args.remaining() < 4) return HELP;

    string id = args.String();
    string type = args.String();
    string location = args.String();
    int quantity = args.Int();
    
    if (pharmacy::add_product(id, type, location, quantity)) {
        cout << "Product added successfully" << endl;
    } else {
        cout << "Product already exists" << endl;
    }

    return SUCCESS;
}
