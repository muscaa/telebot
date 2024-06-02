#pragma once

#include "../utils.h"

namespace pharmacy {

/**
 * @brief Class representing a product in the pharmacy.
 *
 * This class provides methods to access and manipulate product information.
 */
class Product {
private:
    string uid;
    string name;
    string type;
    string location;
    int quantity;

public:
    /**
     * @brief Constructs a Product object.
     *
     * This constructor initializes the Product object with the given parameters.
     *
     * @param uid The unique identifier of the product.
     * @param name The name of the product.
     * @param type The type/category of the product.
     * @param location The location of the product in the pharmacy.
     * @param quantity The quantity of the product available.
     */
    Product(string uid, string name, string type, string location, int quantity)
        : uid(uid), name(name), type(type), location(location), quantity(quantity) {}

    /**
     * @brief Gets the unique identifier of the product.
     *
     * @return The unique identifier of the product.
     */
    string getUID() const { return uid; }

    /**
     * @brief Gets the name of the product.
     *
     * @return The name of the product.
     */
    string getName() const { return name; }

    /**
     * @brief Gets the type/category of the product.
     *
     * @return The type/category of the product.
     */
    string getType() const { return type; }

    /**
     * @brief Gets the location of the product in the pharmacy.
     *
     * @return The location of the product.
     */
    string getLocation() const { return location; }

    /**
     * @brief Gets the quantity of the product available.
     *
     * @return The quantity of the product available.
     */
    int getQuantity() const { return quantity; }

    /**
     * @brief Gets the available quantity of the product.
     *
     * This function returns the available quantity of the product.
     *
     * @return The available quantity of the product.
     */
    int getAvailableQuantity();
};

/**
 * @brief Class representing a reservation in the pharmacy.
 *
 * This class provides methods to access and manipulate reservation information.
 */
class Reservation {
private:
    string uid;
    shared_ptr<Product> product;
    int quantity;
    string name;

public:
    /**
     * @brief Constructs a Reservation object.
     *
     * This constructor initializes the Reservation object with the given parameters.
     *
     * @param uid The unique identifier of the reservation.
     * @param product The product associated with the reservation.
     * @param quantity The quantity of the product reserved.
     * @param name The name of the person who made the reservation.
     */
    Reservation(string uid, shared_ptr<Product> product, int quantity, string name)
        : uid(uid), product(product), quantity(quantity), name(name) {}

    /**
     * @brief Gets the unique identifier of the reservation.
     *
     * @return The unique identifier of the reservation.
     */
    string getUID() const { return uid; }

    /**
     * @brief Gets the product associated with the reservation.
     *
     * @return The product associated with the reservation.
     */
    shared_ptr<Product>& getProduct() { return product; }

    /**
     * @brief Gets the quantity of the product reserved.
     *
     * @return The quantity of the product reserved.
     */
    int getQuantity() const { return quantity; }

    /**
     * @brief Gets the name of the person who made the reservation.
     *
     * @return The name of the person who made the reservation.
     */
    string getName() const { return name; }
};

/**
 * @brief A map to store products with their unique identifiers.
 */
extern map<string, shared_ptr<Product>> products;

/**
 * @brief A map to store reservations with their unique identifiers.
 */
extern map<string, shared_ptr<Reservation>> reservations;

/**
 * @brief Initializes the pharmacy system.
 *
 * This function initializes the pharmacy system, setting up necessary resources.
 */
void init();

/**
 * @brief Adds a product to the pharmacy.
 *
 * This function adds a new product to the pharmacy with the given parameters.
 *
 * @param name The name of the product.
 * @param type The type/category of the product.
 * @param location The location of the product in the pharmacy.
 * @param quantity The quantity of the product available.
 */
void add_product(string name, string type, string location, int quantity);

/**
 * @brief Removes a product from the pharmacy.
 *
 * This function removes a product from the pharmacy based on its unique identifier.
 *
 * @param uid The unique identifier of the product to remove.
 * @return True if the product was successfully removed, false otherwise.
 */
bool remove_product(string uid);

/**
 * @brief Checks if a product exists in the pharmacy.
 *
 * This function checks if a product with the given unique identifier exists in the pharmacy.
 *
 * @param uid The unique identifier of the product to check.
 * @return True if the product exists, false otherwise.
 */
bool product_exists(string uid);

/**
 * @brief Filters products based on a given condition.
 *
 * This function filters the products in the pharmacy based on a specified condition.
 *
 * @param filter The condition to filter products.
 * @return A vector of shared pointers to the products that match the filter condition.
 */
vector<shared_ptr<Product>> filter_products(function<bool(shared_ptr<Product>)> filter);

/**
 * @brief Adds a reservation to the pharmacy.
 *
 * This function adds a new reservation for a product in the pharmacy.
 *
 * @param productUID The unique identifier of the product to reserve.
 * @param quantity The quantity of the product to reserve.
 * @param name The name of the person making the reservation.
 * @return 0 if the reservation was successful, 1 if the product was not found, 2 if the quantity is not available.
 */
int add_reservation(string productUID, int quantity, string name);

/**
 * @brief Removes a reservation from the pharmacy.
 *
 * This function removes a reservation from the pharmacy based on its unique identifier.
 *
 * @param uid The unique identifier of the reservation to remove.
 * @return True if the reservation was successfully removed, false otherwise.
 */
bool remove_reservation(string uid);

/**
 * @brief Checks if a reservation exists in the pharmacy.
 *
 * This function checks if a reservation with the given unique identifier exists in the pharmacy.
 *
 * @param uid The unique identifier of the reservation to check.
 * @return True if the reservation exists, false otherwise.
 */
bool reservation_exists(string uid);

/**
 * @brief Filters reservations based on a given condition.
 *
 * This function filters the reservations in the pharmacy based on a specified condition.
 *
 * @param filter The condition to filter reservations.
 * @return A vector of shared pointers to the reservations that match the filter condition.
 */
vector<shared_ptr<Reservation>> filter_reservations(function<bool(shared_ptr<Reservation>)> filter);

}
