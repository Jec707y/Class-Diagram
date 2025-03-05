#include <iostream>
#include <string>
#include <iomanip>  

using namespace std;

class Product {
private:
    string productID;
    string name;
    double price;
    int stockQuantity;

public:
    Product(string id, string n, double p, int s) : productID(id), name(n), price(p), stockQuantity(s) {}
    
    string getID() const { return productID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stockQuantity; }

    void reduceStock(int quantity) { stockQuantity -= quantity; }
};

class ShoppingCart {
private:
    pair<Product*, int> items[100];
    int itemCount;
    double totalPrice;

public:
    ShoppingCart() : itemCount(0), totalPrice(0.0) {}
    
    void addProduct(Product* product, int quantity) {
        if (product->getStock() >= quantity) {
            items[itemCount++] = make_pair(product, quantity);
            totalPrice += product->getPrice() * quantity;
            product->reduceStock(quantity);
            cout << "Product added successfully!" << endl;
        } else {
            cout << "Not enough stock available!" << endl;
        }
    }
    
    void viewCart() const {
        cout << "\nShopping Cart:" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << left << setw(15) << "Product ID" 
             << setw(20) << "Name" 
             << setw(10) << "Price" 
             << setw(10) << "Quantity" << endl;
        cout << "-------------------------------------------------------------" << endl;

        for (int i = 0; i < itemCount; i++) {
            cout << left << setw(15) << items[i].first->getID()
                 << setw(20) << items[i].first->getName()
                 << setw(10) << items[i].first->getPrice()
                 << setw(10) << items[i].second << endl;
        }
    }
    
    double getTotalPrice() const { return totalPrice; }
    int getItemCount() const { return itemCount; }
    const pair<Product*, int>* getItems() const { return items; } 
};

class Order {
private:
    int orderID;
    ShoppingCart cart;
    double totalAmount;

public:
    Order() : orderID(0), totalAmount(0.0) {} 
    Order(int id, const ShoppingCart& c) : orderID(id), cart(c), totalAmount(c.getTotalPrice()) {}
    
    void displayOrder() const {
        cout << "\nOrder ID: " << orderID << endl;
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Order Details: " << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << left << setw(15) << "Product ID" 
             << setw(20) << "Name" 
             << setw(10) << "Price" 
             << setw(10) << "Quantity" << endl;
        cout << "-------------------------------------------------------------" << endl;

        for (int i = 0; i < cart.getItemCount(); i++) {
            cout << left << setw(15) << cart.getItems()[i].first->getID()
                 << setw(20) << cart.getItems()[i].first->getName()
                 << setw(10) << cart.getItems()[i].first->getPrice()
                 << setw(10) << cart.getItems()[i].second << endl;
        }
    }
};

void displayMenu(Product* products, int productCount, ShoppingCart& cart, Order orders[], int& orderCount) {
    int choice, orderID = 1;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. View Products" << endl;
        cout << "2. View Shopping Cart" << endl;
        cout << "3. View Orders" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "\nAvailable Products:" << endl;
                cout << "------------------------------------------------------" << endl;
                cout << left << setw(15) << "Product ID" 
                     << setw(20) << "Name" 
                     << setw(10) << "Price" << endl;
                cout << "------------------------------------------------------" << endl;

                for (int i = 0; i < productCount; i++) {
                    cout << left << setw(15) << products[i].getID()
                         << setw(20) << products[i].getName()
                         << setw(10) << products[i].getPrice() << endl;
                }
                string productID;
                int quantity;
                cout << "Enter the Product ID you want to add to the cart: ";
                cin >> productID;
                cout << "Enter quantity: ";
                cin >> quantity;
                for (int i = 0; i < productCount; i++) {
                    if (products[i].getID() == productID) {
                        cart.addProduct(&products[i], quantity);
                        break;
                    }
                }
                break;
            }
            case 2:
                cart.viewCart();
                cout << "Do you want to check out all products? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    if (orderCount < 100) {
                        orders[orderCount++] = Order(orderID++, cart);
                        cout << "You have successfully checked out the products!" << endl;
                        cart = ShoppingCart();
                    }
                }
                break;
            case 3:
                for (int i = 0; i < orderCount; i++) {
                    orders[i].displayOrder();
                }
                break;
        }
    } while (choice != 4);
}

int main() {
    Product products[] = {
        Product("ABC", "Paper", 20, 10),
        Product("CDE", "Pencil", 10, 20),
        Product("QWE", "Paper", 20, 15),
        Product("TRE", "Pencil", 10, 25),
        Product("ASD", "Paper", 20, 10),
        Product("ZXC", "Pencil", 10, 30)
    };
    int productCount = 6;
    
    ShoppingCart cart;
    Order orders[100];
    int orderCount = 0;
    
    displayMenu(products, productCount, cart, orders, orderCount);
    return 0;
}
