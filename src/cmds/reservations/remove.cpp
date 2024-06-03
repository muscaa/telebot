#include "cmds/reservations/remove.hpp"

int cmds::reservations::Remove::execute(utils::Args args) {
    if (args.remaining() == 0) return HELP;

    for (int i = 0; i < args.remaining(); i++) {
        string uid = args.String();

        if (pharmacy::remove_reservation(uid)) {
            cout << "Reservation removed successfully!" << endl;
        } else {
            cout << "Reservation not found!" << endl;
        }
    }

    return SUCCESS;
}
