#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Structure for menu items
struct MenuItem {
    int id;
    string name;
    float price;
    int stock;
};

// Structure for customer orders
struct Order {
    int orderId;
    MenuItem item;
    int quantity;
    float total;
};

// Admin login credentials
const string USERNAME = "Gautam";
const string PASSWORD = "Gautam12";

// Function to print a header with decoration
void printHeader(const string& header) {
    cout << "=====================================\n";
    cout << "           " << header << "\n";
    cout << "=====================================\n";
}

// Function to display the menu
void displayMenu(const vector<MenuItem>& menu) {
    printHeader("Cafe Menu");
    for (const auto& item : menu) {
        cout << item.id << ". " << setw(20) << left << item.name
                  << "$" << fixed << setprecision(2) << item.price
                  << " (Stock: " << item.stock << ")\n";
    }
    cout << "=====================================\n";
}

// Function to handle admin login
bool adminLogin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    if (username == USERNAME && password == PASSWORD) {
        cout << "Login Successful!\n";
        return true;
    } else {
        cout << "Invalid credentials. Try again.\n";
        return false;
    }
}

// Function to update menu items
void updateMenu(vector<MenuItem>& menu) {
    int choice;
    printHeader("Update Menu");

    cout << "1. Add Item\n2. Remove Item\n3. Change Price\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) {
        MenuItem newItem;
        cout << "Enter Item Name: ";
        cin.ignore(); // To consume leftover newline
        getline(cin, newItem.name);
        cout << "Enter Item Price: ";
        cin >> newItem.price;
        cout << "Enter Item Stock: ";
        cin >> newItem.stock;
        newItem.id = menu.size() + 1;
        menu.push_back(newItem);
    } else if (choice == 2) {
        int removeId;
        cout << "Enter Item ID to Remove: ";
        cin >> removeId;
        if (removeId > 0 && removeId <= menu.size()) {
            menu.erase(menu.begin() + removeId - 1);
            for (size_t i = 0; i < menu.size(); ++i) {
                menu[i].id = i + 1;
            }
        } else {
            cout << "Invalid Item ID!\n";
        }
    } else if (choice == 3) {
        int id;
        cout << "Enter Item ID to Change Price: ";
        cin >> id;
        if (id > 0 && id <= menu.size()) {
            cout << "Enter New Price: ";
            cin >> menu[id - 1].price;
        } else {
            cout << "Invalid Item ID!\n";
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// Function to take orders
void takeOrder(vector<MenuItem>& menu, Order& order) {
    int itemId, quantity;
    printHeader("Take Order");

    cout << "Enter Item ID: ";
    cin >> itemId;
    if (itemId > 0 && itemId <= menu.size()) {
        cout << "Enter Quantity: ";
        cin >> quantity;
        if (menu[itemId - 1].stock >= quantity) {
            menu[itemId - 1].stock -= quantity;
            order.orderId = rand() % 1000;
            order.item = menu[itemId - 1];
            order.quantity = quantity;
            order.total = order.item.price * quantity;
            cout << "Order ID: " << order.orderId << "\n";
            cout << "Total Bill: $" << fixed << setprecision(2) << order.total << "\n";
        } else {
            cout << "Insufficient stock!\n";
        }
    } else {
        cout << "Invalid Item ID!\n";
    }
}

int main() {
    vector<MenuItem> menu = {
        {1, "Coffee", 5.0, 10},
        {2, "Tea", 3.0, 15},
        {3, "Sandwich", 8.0, 20}
    };
    Order order;

    if (adminLogin()) {
        int choice;
        do {
            printHeader("Cafe Management System");
            cout << "1. Display Menu\n2. Update Menu\n3. Take Order\n4. Exit\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayMenu(menu);
                    break;
                case 2:
                    updateMenu(menu);
                    break;
                case 3:
                    takeOrder(menu, order);
                    break;
                case 4:
                    cout << "Exiting Cafe Management System.\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
            }
        } while (choice != 4);
    }

    return 0;
}
