#include "pharmacy.h"

#define CONFIG_FILE "products.dat"
#define UID_LENGTH 4

vector<shared_ptr<pharmacy::Product>> pharmacy::products = vector<shared_ptr<pharmacy::Product>>();
map<string, unique_ptr<pharmacy::Reservation>> pharmacy::reservations = map<string, unique_ptr<pharmacy::Reservation>>();

static void save_products() {
    utils::ConfigWriter out(CONFIG_FILE);

    out.Int(pharmacy::products.size());
    for (shared_ptr<pharmacy::Product>& p : pharmacy::products) {
        out.LenString(p->getID());
        out.LenString(p->getType());
        out.LenString(p->getLocation());
        out.Int(p->getQuantity());

        /*out.Int(p->reservations->length);
        for (int j = 0; j < p->reservations->length; j++) {
            reservation r = mcall(p->reservations, get, j);

            out.Bytes(r->uid->data, UID_LENGTH);
            out.LenString(r->name);
            out.Int(r->quantity);
        }*/
    }

    out.close();
}

static void load_products() {
    pharmacy::reservations.clear();
    pharmacy::products.clear();

    if (!filesystem::exists(CONFIG_FILE)) return;

    utils::ConfigReader in(CONFIG_FILE);

    int products_length = in.Int();
    for (int i = 0; i < products_length; i++) {
        string id = in.LenString();
        string type = in.LenString();
        string location = in.LenString();
        int quantity = in.Int();

        auto p = make_shared<pharmacy::Product>(id, type, location, quantity);

        /*int reservations_length = in.Int();
        for (int j = 0; j < reservations_length; j++) {
            HASH uid = new(HASH, UID_LENGTH, in.Bytes(UID_LENGTH));
            string name = in.LenString();
            int quantity = in.Int();

            mcall(p->reservations, add, new(reservation, uid, p, name, quantity));
        }*/

        pharmacy::products.push_back(p);
    }
    
    in.close();
}

int pharmacy::Product::getAvailableQuantity() {
    int index = find_product(id);
    if (index == -1) return -1;

    int available = quantity;

    for (auto it = reservations.begin(); it != reservations.end(); it++) {
        if (it->second->getProduct()->getID() == id) {
            available -= it->second->getQuantity();
        }
    }

    return available;
}

void pharmacy::init() {
    load_products();
}

bool pharmacy::add_product(string id, string type, string location, int quantity) {
    if (product_exists(id)) return false;

    products.push_back(make_shared<pharmacy::Product>(id, type, location, quantity));

    save_products();

    return true;
}

bool pharmacy::remove_product(string id) {
    int index = find_product(id);
    if (index == -1) return false;

    for (auto it = reservations.begin(); it != reservations.end();) {
        if (it->second->getProduct()->getID() == id) {
            it = reservations.erase(it);
        } else {
            it++;
        }
    }

    products.erase(products.begin() + index);

    save_products();

    return true;
}

int pharmacy::find_product(string id) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i]->getID() == id) return i;
    }
    return -1;
}

bool pharmacy::product_exists(string id) {
    return find_product(id) != -1;
}

bool pharmacy::add_reservation(string product, int quantity, string name) {
    int index = find_product(product);
    if (index == -1) return false;

    shared_ptr<Product> p = products[index];
    if (quantity > p->getAvailableQuantity()) return false;

    string uid;
    do {
        uid = utils::HASH::random(UID_LENGTH).toHex();
    } while (reservation_exists(uid));

    reservations[uid] = make_unique<Reservation>(uid, p, quantity, name);

    save_products();

    return true;
}

bool pharmacy::remove_reservation(string uid) {
    if (!reservation_exists(uid)) return false;

    reservations.erase(uid);

    save_products();

    return true;
}

bool pharmacy::reservation_exists(string uid) {
    return reservations.find(uid) != reservations.end();
}
