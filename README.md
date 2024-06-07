
# University C++ Projects

[![License: Apache 2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Requested Applications

### #1. Pharmacy products reservation system rewrite

The app allows adding/deleting a product with name, type and location,
displaying all products and reservations, searching for a product by name
and availability, reserving the product and canceling the reservation.
All using just the command line.

#### Commands

<details>
<summary>Show Product(s)</summary>

  ```bash
  products show [uid]
  ```
  Displays information for products or a specific product with the specified product UID.
</details>

<details>
<summary>Find Product(s)</summary>

  ```bash
  products find uid=[value] name=[value] type=[value] location=[value] quantity=[value]
  ```
  Finds products in the system with the specified uid, name, type, location and/or quantity.
</details>

<details>
<summary>Add Product</summary>

  ```bash
  products add <name> <type> <location> <quantity>
  ```
  Adds a product to the system with the specified name, type, location and quantity.
</details>

<details>
<summary>Remove Product(s)</summary>

  ```bash
  products remove <uid...>
  ```
  Removes a product or more from the system with the specified product UID.
</details>

<details>
<summary>Show Reservation(s)</summary>

  ```bash
  reservations show [uid]
  ```
  Displays information for reservations or a specific reservation with the specified reservation UID.
</details>

<details>
<summary>Find Reservation(s)</summary>

  ```bash
  reservations find uid=[value] productUID=[value] quantity=[value] name=[value]
  ```
  Finds reservations in the system with the specified uid, product UID, quantity and/or name.
</details>

<details>
<summary>Add Reservation</summary>

  ```bash
  reservations add <productUID> <quantity> <name>
  ```
  Adds a reservation to the system with the specified product UID, quantity and name.
</details>

<details>
<summary>Remove Reservation(s)</summary>

  ```bash
  reservations remove <uid...>
  ```
  Removes a reservation or more from the system with the specified reservation UID.
</details>

Everything is written in `config/pharmacy.dat`.

## Building/Running from source with `gcc`

<details>
<summary>Windows</summary>

  ```batch
  build_and_run.bat
  ```
</details>

<details>
<summary>Linux</summary>

  ```bash
  chmod +x setup.sh && ./setup.sh
  ```
  
  then
  
  ```bash
  ./build_and_run.sh
  ```
</details>
