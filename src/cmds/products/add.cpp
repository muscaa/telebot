#include "cmds/products/add.hpp"

int cmds::products::Add::execute(utils::Args args) {
    if (args.remaining() != 4) return HELP;

    string name = args.String();
    string type = args.String();
    string location = args.String();
    int quantity = args.Int();
    
    pharmacy::add_product(name, type, location, quantity);
    cout << "Product added successfully!" << endl;

    return SUCCESS;
}
