#include "add.h"

int cmds::reservations::Add::execute(utils::Args args) {
    if (args.remaining() != 3) return HELP;

    string productUID = args.String();
    int quantity = args.Int();
    string name = args.String();

    int result = pharmacy::add_reservation(productUID, quantity, name);

    if (result == 0) {
        cout << "Reservation added successfully!" << endl;
    } else if (result == 1) {
        cout << "Product not found!" << endl;
    } else if (result == 2) {
        cout << "Not enough quantity available!" << endl;
    }

    return SUCCESS;
}
