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

    int getAvailableQuantity();
};

class Reservation {
private:
    string uid;
    shared_ptr<Product> product;
    int quantity;
    string name;

public:
    Reservation(string uid, shared_ptr<Product> product, int quantity, string name)
        : uid(uid), product(product), quantity(quantity), name(name) {}

    string getUID() { return uid; }

    shared_ptr<Product>& getProduct() { return product; }

    int getQuantity() { return quantity; }

    string getName() { return name; }
};

extern vector<shared_ptr<pharmacy::Product>> products;
extern map<string, unique_ptr<pharmacy::Reservation>> reservations;

void init();

bool add_product(string id, string type, string location, int quantity);

bool remove_product(string id);

int find_product(string id);

bool product_exists(string id);

bool add_reservation(string product, int quantity, string name);

bool remove_reservation(string uid);

bool reservation_exists(string uid);

}
