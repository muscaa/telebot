#include "pharmacy.h"

#define CONFIG_FILE "products.dat"
#define UID_LENGTH 4

static vector<shared_ptr<pharmacy::Product>> products = vector<shared_ptr<pharmacy::Product>>();
static map<string, unique_ptr<pharmacy::Reservation>> reservations = map<string, unique_ptr<pharmacy::Reservation>>();

static void save_products() {
    /*string parent = file_parent(CONFIG_FILE);
    if (parent != NULL) dir_create(parent);

    config_writer out = push_save_config(CONFIG_FILE);
    out.Int(products->length);
    for (int i = 0; i < products->length; i++) {
        product p = mcall(products, get, i);

        out.LenString(p->name);
        out.LenString(p->type);
        out.LenString(p->location);
        out.Int(p->quantity);

        out.Int(p->reservations->length);
        for (int j = 0; j < p->reservations->length; j++) {
            reservation r = mcall(p->reservations, get, j);

            out.Bytes(r->uid->data, UID_LENGTH);
            out.LenString(r->name);
            out.Int(r->quantity);
        }
    }
    pop_save_config();*/
}

static void load_products() {
    /*for (int i = 0; i < products->length; i++) {
        product p = mcall(products, get, i);
        for (int j = 0; j < p->reservations->length; j++) {
            reservation r = mcall(p->reservations, get, j);
            delete(r->uid);
            free(r);
        }
        free(p);
    }
    mcall0(products, clear);

    if (!file_exists(CONFIG_FILE)) return;

    config_reader in = push_load_config(CONFIG_FILE);
    int products_length = in.Int();
    for (int i = 0; i < products_length; i++) {
        string name = in.LenString();
        string type = in.LenString();
        string location = in.LenString();
        int quantity = in.Int();

        product p = new(product, name, type, location, quantity);

        int reservations_length = in.Int();
        for (int j = 0; j < reservations_length; j++) {
            HASH uid = new(HASH, UID_LENGTH, in.Bytes(UID_LENGTH));
            string name = in.LenString();
            int quantity = in.Int();

            mcall(p->reservations, add, new(reservation, uid, p, name, quantity));
        }

        mcall(products, add, p);
    }
    pop_load_config();*/
}

static int find_product(string id) {
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i]->getID() == id) return i;
    }
    return -1;
}

static bool product_exists(string id) {
    return find_product(id) != -1;
}

static bool reservation_exists(utils::HASH uid) {
    return reservations.find(uid.toHex()) != reservations.end();
}

static int get_available_quantity(string id) {
    int index = find_product(id);
    if (index == -1) return -1;

    int available = products[index]->getQuantity();

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

bool pharmacy::add_reservation(string product, int quantity, string name) {
    if (!product_exists(product)) return false;
    if (quantity > get_available_quantity(product)) return false;

    utils::HASH uid;
    do {
        uid = utils::HASH::random(UID_LENGTH);
    } while (reservation_exists(uid));

    reservations[uid.toHex()] = make_unique<pharmacy::Reservation>(uid, products[find_product(product)], quantity, name);

    save_products();

    return true;
}

bool pharmacy::remove_reservation(utils::HASH uid) {
    if (!reservation_exists(uid)) return false;

    reservations.erase(uid.toHex());

    save_products();

    return true;
}
