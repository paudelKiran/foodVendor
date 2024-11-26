# Food Vendor System

The **Food Vendor System** is a console-based application for managing food orders and transactions between customers and restaurant owners. It allows customers to browse food items, place orders, and view their transaction history. Restaurant owners can manage their menu items, view transactions, and serve customers.

## Features

### For Customers:
- **Signup/Login**: Customers can create accounts and log in securely.
- **View Food Items**: Browse food items by restaurants or globally.
- **Order Food**: Place orders and generate bills.
- **View Transactions**: Review past orders and transaction details.

### For Restaurant Owners:
- **Signup/Login**: Restaurant owners can register and log in.
- **Manage Menu**: Add, remove, and view food items in their restaurant's menu.
- **View Transactions**: Monitor orders and revenue.

### Data Validations:
- Email validation to ensure proper formatting.
- Password validation (minimum 8 characters).
- Phone number validation (10 digits).

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC) installed on your system.
- Basic understanding of C programming.
- Access to a terminal or console.

### Installation

1. ### Clone the Repository

Clone the repository to your local machine:

```bash
git clone https://github.com/paudelKiran/foodVendor.git
```

After cloning, compile the project using:

```bash
gcc food_vendor.c -o food_vendor
```
## Running the Project

```bash
./food_vendor
```

## How to Use

### For Customers:
1. Choose **Customer Signup** to create a new account.
2. Log in using your registered email and password.
3. Explore food items and place orders as needed.
4. View your order history in the **Transactions** section.

### For Restaurant Owners:
1. Choose **Restaurant Owner Signup** to register your restaurant.
2. Log in to access the restaurant owner panel.
3. Add or remove food items from the menu.
4. View orders and transactions placed by customers.

## Files and Structure
- **`food_vendor.c`**: The main program containing all functionalities.
- **`customers.txt`**: Stores customer data.
- **`restaurant_owners.txt`**: Stores restaurant owner data.
- **`menu.txt`**: Contains food item details for all restaurants.
- **`bill.txt`**: Logs transaction data for billing and review.

## Contributing

Feel free to fork the repository, make changes, and submit a pull request. Please ensure proper code formatting and add comments where necessary.
## License

This project is licensed under the MIT License. You can view or download the full license from the [LICENSE file](license.txt).