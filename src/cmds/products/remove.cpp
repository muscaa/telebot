#include "remove.h"

int cmds::products::Remove::execute(utils::Args args) {
    if (args.remaining() == 0) return HELP;

    for (int i = 0; i < args.remaining(); i++) {
        string uid = args.String();

        if (pharmacy::remove_product(uid)) {
            cout << "Product removed successfully!" << endl;
        } else {
            cout << "Product not found!" << endl;
        }
    }

    return SUCCESS;
}
