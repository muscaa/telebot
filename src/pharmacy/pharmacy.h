#pragma once

#include "../utils.h"

namespace pharmacy {

class Product {
private:
    string uid;
    string name;
    string type;
    string location;
    int quantity;
    
public:
    Product(string uid, string name, string type, string location, int quantity)
        : uid(uid), name(name), type(type), location(location), quantity(quantity) {}

    string getUID() { return uid; }

    string getName() { return name; }

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

extern map<string, shared_ptr<Product>> products;
extern map<string, shared_ptr<Reservation>> reservations;

void init();

void add_product(string name, string type, string location, int quantity);

bool remove_product(string uid);

bool product_exists(string uid);

vector<shared_ptr<Product>> filter_products(function<bool(shared_ptr<Product>)> filter);

// 0 - success, 1 - product not found, 2 - quantity not available
int add_reservation(string productUID, int quantity, string name);

bool remove_reservation(string uid);

bool reservation_exists(string uid);

vector<shared_ptr<Reservation>> filter_reservations(function<bool(shared_ptr<Reservation>)> filter);

}
