#include "cmds/reservations/find.hpp"

#include "cmds/reservations/show.hpp"

int cmds::reservations::Find::execute(utils::Args args) {
    if (args.remaining() == 0) return HELP;

    string uid_filter = "";
    string productUID_filter = "";
    int quantity_filter = -1;
    string name_filter = "";

    while (args.remaining() > 0) {
        string arg = utils::lower(args.String());

        if (arg.find("uid=") == 0) {
            uid_filter = arg.substr(4);
        } else if (arg.find("productuid=") == 0) {
            productUID_filter = arg.substr(11);
        } else if (arg.find("quantity=") == 0) {
            quantity_filter = stoi(arg.substr(9));
        } else if (arg.find("name=") == 0) {
            name_filter = arg.substr(5);
        } else {
            cout << "Invalid argument: " << arg << endl;
            return FAIL;
        }
    }

    auto filtered = pharmacy::filter_reservations([&](shared_ptr<pharmacy::Reservation> r) {
        string uid = utils::lower(r->getUID());
        string productUID = utils::lower(r->getProduct()->getUID());
        int quantity = r->getQuantity();
        string name = utils::lower(r->getName());

        if (!uid_filter.empty() && uid.find(uid_filter) == string::npos) return false;
        if (!productUID_filter.empty() && productUID.find(productUID_filter) == string::npos) return false;
        if (quantity_filter > -1 && quantity != quantity_filter) return false;
        if (!name_filter.empty() && name.find(name_filter) == string::npos) return false;

        return true;
    });

    cmds::reservations::Show::display_header_horizontal();
    for (auto& r : filtered) {
        cmds::reservations::Show::display_reservation_horizontal(r);
    }

    return SUCCESS;
}
