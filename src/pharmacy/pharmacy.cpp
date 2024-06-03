#include "pharmacy/pharmacy.hpp"

#define CONFIG_FILE "pharmacy.dat"
#define UID_LENGTH 4

map<string, shared_ptr<pharmacy::Product>> pharmacy::products = map<string, shared_ptr<pharmacy::Product>>();
map<string, shared_ptr<pharmacy::Reservation>> pharmacy::reservations = map<string, shared_ptr<pharmacy::Reservation>>();

static void save_products() {
    utils::ConfigWriter out(CONFIG_FILE);

    out.Int(pharmacy::products.size());
    for (auto& pair : pharmacy::products) {
        auto p = pair.second;

        byte buid[UID_LENGTH];
        utils::hex_bytes(buid, p->getUID());

        out.Bytes(buid, UID_LENGTH);
        out.LenString(p->getName());
        out.LenString(p->getType());
        out.LenString(p->getLocation());
        out.Int(p->getQuantity());
    }

    out.Int(pharmacy::reservations.size());
    for (auto& pair : pharmacy::reservations) {
        auto r = pair.second;

        byte buid[UID_LENGTH];
        utils::hex_bytes(buid, r->getUID());

        out.Bytes(buid, UID_LENGTH);
        out.LenString(r->getProduct()->getUID());
        out.Int(r->getQuantity());
        out.LenString(r->getName());
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
        byte buid[UID_LENGTH];
        in.Bytes(buid, UID_LENGTH);

        string uid = utils::hex_string(buid, UID_LENGTH);
        string name = in.LenString();
        string type = in.LenString();
        string location = in.LenString();
        int quantity = in.Int();

        pharmacy::products[uid] = make_shared<pharmacy::Product>(uid, name, type, location, quantity);
    }

    int reservations_length = in.Int();
    for (int i = 0; i < reservations_length; i++) {
        byte buid[UID_LENGTH];
        in.Bytes(buid, UID_LENGTH);

        string uid = utils::hex_string(buid, UID_LENGTH);
        string productUID = in.LenString();
        int quantity = in.Int();
        string name = in.LenString();

        pharmacy::reservations[uid] = make_shared<pharmacy::Reservation>(uid, pharmacy::products[productUID], quantity, name);
    }
    
    in.close();
}

int pharmacy::Product::getAvailableQuantity() {
    if (!product_exists(uid)) return -1;

    int available = quantity;

    for (auto& pair : reservations) {
        if (pair.second->getProduct()->getUID() == uid) {
            available -= pair.second->getQuantity();
        }
    }

    return available;
}

void pharmacy::init() {
    load_products();
}

void pharmacy::add_product(string name, string type, string location, int quantity) {
    string uid;
    do {
        uid = utils::HASH::random(UID_LENGTH).toHex();
    } while (product_exists(uid));

    products[uid] = make_shared<Product>(uid, name, type, location, quantity);

    save_products();
}

bool pharmacy::remove_product(string uid) {
    if (!product_exists(uid)) return false;

    for (auto it = reservations.begin(); it != reservations.end();) {
        if (it->second->getProduct()->getUID() == uid) {
            it = reservations.erase(it);
        } else {
            it++;
        }
    }

    products.erase(uid);

    save_products();

    return true;
}

bool pharmacy::product_exists(string uid) {
    return products.find(uid) != products.end();
}

vector<shared_ptr<pharmacy::Product>> pharmacy::filter_products(function<bool(shared_ptr<Product>)> filter) {
    vector<shared_ptr<Product>> result;

    for (auto& pair : products) {
        if (filter(pair.second)) {
            result.push_back(pair.second);
        }
    }

    return result;
}

int pharmacy::add_reservation(string productUID, int quantity, string name) {
    if (!product_exists(productUID)) return 1;

    shared_ptr<Product> p = products[productUID];
    if (quantity > p->getAvailableQuantity()) return 2;

    string uid;
    do {
        uid = utils::HASH::random(UID_LENGTH).toHex();
    } while (reservation_exists(uid));

    reservations[uid] = make_shared<Reservation>(uid, p, quantity, name);

    save_products();

    return 0;
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

vector<shared_ptr<pharmacy::Reservation>> pharmacy::filter_reservations(function<bool(shared_ptr<Reservation>)> filter) {
    vector<shared_ptr<Reservation>> result;

    for (auto& pair : reservations) {
        if (filter(pair.second)) {
            result.push_back(pair.second);
        }
    }

    return result;
}
