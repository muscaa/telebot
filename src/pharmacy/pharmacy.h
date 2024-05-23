#pragma once

#include "../utils.h"

namespace pharmacy {

class Product {
private:
    string id;
    string type;
    string location;
    int quantity;
    
public:
    Product(string id, string type, string location, int quantity)
        : id(id), type(type), location(location), quantity(quantity) {}

    string getID() { return id; }

    string getType() { return type; }

    string getLocation() { return location; }

    int getQuantity() { return quantity; }
};

class Reservation {
private:
    utils::HASH uid;
    shared_ptr<Product> product;
    int quantity;
    string name;

public:
    Reservation(utils::HASH uid, shared_ptr<Product> product, int quantity, string name)
        : uid(uid), product(product), quantity(quantity), name(name) {}

    utils::HASH getUID() { return uid; }

    shared_ptr<Product>& getProduct() { return product; }

    int getQuantity() { return quantity; }

    string getName() { return name; }
};

void init();

bool add_product(string id, string type, string location, int quantity);

bool remove_product(string id);

bool add_reservation(string product, int quantity, string name);

bool remove_reservation(utils::HASH uid);

}
