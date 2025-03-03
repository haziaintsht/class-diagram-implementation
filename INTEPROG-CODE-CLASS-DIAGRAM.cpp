#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Product {
public:
    int productID;
    string NameofProduct;
    double PriceofProduct;

    Product() {
        productID = 0;
        NameofProduct = "";
        PriceofProduct = 0.0;
    }
    Product(int ID, string n, double p) {
        productID = ID;
        NameofProduct = n;
        PriceofProduct = p;
    }

    static void displayProducts(Product products[], int size) {
        cout << "=====Item List=====\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << "\n";
        for (int i = 0; i < size; i++) {
            cout << left << setw(10) << products[i].productID
                 << setw(20) << products[i].NameofProduct << "P" << products[i].PriceofProduct << "\n";
        }
    }
};

class Order {
private:
    static int orderCounter;
    int orderID;
    double totalAmount;
    Product productsOrdered[20];
    int orderedQuantities[20];
    int itemCount;

public:
    Order() {
        orderID = 0;
        totalAmount = 0.0;
        itemCount = 0;
    }

    void createOrder(Product cartforshopping[], int quantities[], int size, double amount) {
        if (amount > 0) {
            orderID = ++orderCounter;
            totalAmount = amount;
            for (int i = 0; i < size; i++) {
                productsOrdered[i] = cartforshopping[i];
                orderedQuantities[i] = quantities[i];
            }
            itemCount = size;
        }
    }

    void displayOrderDetails() const {
        if (orderID != 0) {
            cout << "\nOrder ID: " << orderID << "\n";
            cout << "Total Amount: P" << totalAmount << "\n";
            cout << "Order Details:\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(10) << "Price"
                 << setw(10) << "Quantity" << "\n";
            for (int i = 0; i < itemCount; i++) {
                cout << left << setw(10) << productsOrdered[i].productID
                     << setw(20) << productsOrdered[i].NameofProduct
                     << setw(10) << productsOrdered[i].PriceofProduct
                     << setw(10) << orderedQuantities[i] << "\n";
            }
        }
    }
};
int Order::orderCounter = 0;

class ShoppingCart {
private:
    Product cartforshopping[20];
    int quantities[20];
    int itemCount;

public:
    ShoppingCart() {
        itemCount = 0;
    }

    void addProduct(Product products[], int size, int id) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (products[i].productID == id) {
                found = true;
                bool inCart = false;
                for (int j = 0; j < itemCount; j++) {
                    if (cartforshopping[j].productID == id) {
                        quantities[j]++;
                        inCart = true;
                        break;
                    }
                }
                if (!inCart) {
                    cartforshopping[itemCount] = products[i];
                    quantities[itemCount] = 1;
                    itemCount++;
                }
                cout << "Product added successfully!\n";
                break;
            }
        }
        if (!found) {
            cout << "No product ID found.\n";
        }
    }

    void displayCart() const {
        if (itemCount == 0) {
            cout << "Shopping cart is empty!\n";
            return;
        }
        cout << "\nShopping Cart:\n";
        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Price"
             << setw(10) << "Quantity" << "\n";

        for (int i = 0; i < itemCount; i++) {
            cout << left << setw(10) << cartforshopping[i].productID
                 << setw(20) << cartforshopping[i].NameofProduct
                 << setw(10) << cartforshopping[i].PriceofProduct
                 << setw(10) << quantities[i] << "\n";
        }
    }

    double checkout(Order &order) {
    if (itemCount == 0) {
        cout << "No products to checkout.\n";
        return 0.0;
    }

    cout << "\n===== Checkout Summary =====\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << setw(10) << "Total" << "\n";

    double totalAmount = 0.0;
    for (int i = 0; i < itemCount; i++) {
        double itemTotal = cartforshopping[i].PriceofProduct * quantities[i];
        totalAmount += itemTotal;
        cout << left << setw(10) << cartforshopping[i].productID
             << setw(20) << cartforshopping[i].NameofProduct
             << setw(10) << cartforshopping[i].PriceofProduct
             << setw(10) << quantities[i]
             << setw(10) << itemTotal << "\n";
    }
    
    cout << "Total Amount: P" << totalAmount << "\n";

    char choice;
    do {
        cout << "Do you want to confirm checkout? (Y/N): ";
        cin >> choice;
        if (cin.fail() || (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')) {
            cout << "Invalid input! Please enter Y or N.\n";
            cin.clear();
            while (cin.get() != '\n'); 
        }
    } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

    if (choice == 'Y' || choice == 'y') {
        order.createOrder(cartforshopping, quantities, itemCount, totalAmount);
        cout << "You have successfully checked out the products!\n";
        itemCount = 0;
        return totalAmount;
    } else {
        cout << "Checkout canceled. Returning to menu...\n";
        return 0.0;
    }
}

    bool isEmpty() const {
        return itemCount == 0;
    }
};

void validateNumInput(int &input) {
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cout << "Invalid input! Please enter a number: ";
            cin.clear();
            while (cin.get() != '\n');
        } else {
            while (cin.get() != '\n'); 
            break;
        }
    }
}

char validateCharInput() {
    char c;
    while (true) {
        cin >> c;
        if (cin.fail() || (c != 'Y' && c != 'y' && c != 'N' && c != 'n')) {
            cout << "Invalid input! Please enter Y or N: ";
            cin.clear();
            while (cin.get() != '\n'); 
        } else {
            while (cin.get() != '\n'); 
            return c;
        }
    }
}

int main() {
    Product products[] = {
         Product(1, "Pencil", 12.00),
        Product(2, "Eraser", 8.00),
        Product(3, "Ruler", 15.00),
        Product(4, "Yellow Paper", 60.00),
        Product(5, "Ballpen", 25.00)
    };

    ShoppingCart cartforshopping;
    Order orders[10];
    int orderCount = 0;
    int choice;

    do {
        cout << "\n===== Menu =====\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        validateNumInput(choice);

        if (choice == 1) {
            char addMore;
            do {
                Product::displayProducts(products, 5);
                cout << "Enter the ID of the product you want to add to the shopping cart: ";
                int productId;
                validateNumInput(productId);
                cartforshopping.addProduct(products, 5, productId);

                cout << "Do you want to add another product? (Y/N): ";
                addMore = validateCharInput();
            } while (addMore == 'Y' || addMore == 'y');
        } 
        else if (choice == 2) {
            cartforshopping.displayCart();
            if (!cartforshopping.isEmpty() && orderCount < 10) {
                cartforshopping.checkout(orders[orderCount]);
                orderCount++;
            }
        } 
        else if (choice == 3) {
            if (orderCount == 0) cout << "No orders placed yet.\n";
            else for (int i = 0; i < orderCount; i++) orders[i].displayOrderDetails();
        } 
    } while (choice != 4);

    return 0;
}