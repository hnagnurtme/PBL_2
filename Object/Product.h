#include <string>
#include <iostream>

using namespace std;

class Product {
public:
    // Constructor
    Product(const string& id, const string& name, double price, const string& imagePath)
        : productId(id), productName(name), productPrice(price), productImage(imagePath) {}

    // Getters
    string getId() const { return productId; }
    string getName() const { return productName; }
    double getPrice() const { return productPrice; }
    string getImage() const { return productImage; }

    // Method to display product information
    void displayInfo() const {
        cout << "Product ID: " << productId << endl;
        cout << "Product Name: " << productName << endl;
        cout << "Price: " << productPrice << " VND" << endl;
        cout << "Image Path: " << productImage << endl;
    }

private:
    string productId;     // Product ID
    string productName;   // Product name
    double productPrice;  // Product price
    string productImage;  // Image path
};
