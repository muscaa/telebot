#include "cmds/products/find.hpp"

#include "cmds/products/show.hpp"

int cmds::products::Find::execute(utils::Args args) {
    if (args.remaining() == 0) return HELP;

    string uid_filter = "";
    string name_filter = "";
    string type_filter = "";
    string location_filter = "";
    int quantity_filter = -1;

    while (args.remaining() > 0) {
        string arg = utils::lower(args.String());

        if (arg.find("uid=") == 0) {
            uid_filter = arg.substr(4);
        } else if (arg.find("name=") == 0) {
            name_filter = arg.substr(5);
        } else if (arg.find("type=") == 0) {
            type_filter = arg.substr(5);
        } else if (arg.find("location=") == 0) {
            location_filter = arg.substr(9);
        } else if (arg.find("quantity=") == 0) {
            quantity_filter = stoi(arg.substr(9));
        } else {
            cout << "Invalid argument: " << arg << endl;
            return FAIL;
        }
    }

    auto filtered = pharmacy::filter_products([&](shared_ptr<pharmacy::Product> p) {
        string uid = utils::lower(p->getUID());
        string name = utils::lower(p->getName());
        string type = utils::lower(p->getType());
        string location = utils::lower(p->getLocation());
        int quantity = p->getQuantity();

        if (!uid_filter.empty() && uid.find(uid_filter) == string::npos) return false;
        if (!name_filter.empty() && name.find(name_filter) == string::npos) return false;
        if (!type_filter.empty() && type.find(type_filter) == string::npos) return false;
        if (!location_filter.empty() && location.find(location_filter) == string::npos) return false;
        if (quantity_filter > -1 && quantity != quantity_filter) return false;

        return true;
    });

    cmds::products::Show::display_header_horizontal();
    for (auto& p : filtered) {
        cmds::products::Show::display_product_horizontal(p);
    }

    return SUCCESS;
}
