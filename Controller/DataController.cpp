#include "Controller/DataController.h"
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"
#include "Model/Product.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
using namespace std;

void DataController:: setProductFileName(const string& filename){
    productFileName = filename;
}


Vector<Product> DataController::loadProductData() {
    Vector<Product> products;
    ifstream file(productFileName);

    std::cout << "Trying to open file: " << productFileName << std::endl; 

    if (!file.is_open()) {
        throw runtime_error("Không thể mở file: " + productFileName);
    }

    string line;
    while (getline(file, line)) {
        Product product = parseProduct(line);
        products.pushback(product); 
    }

    file.close();
    return products;
}

Product DataController::parseProduct(const string& line) {
    istringstream ss(line);
    string id, name, category, priceStr, stockStr, description, sizesStr, colorsStr, brand;

    getline(ss, id, ';');         
    getline(ss, name, ';');
    getline(ss, category, ';');
    getline(ss, priceStr, ';');
    getline(ss, stockStr, ';');
    getline(ss, description, ';');
    getline(ss, colorsStr, ';');
    getline(ss, brand, ';');

    double price = stod(priceStr);
    int stock = stoi(stockStr);

    Vector<string> colors;
    istringstream colorsStream(colorsStr);
    string color;

    while (getline(colorsStream, color, ',')) {
        color.erase(remove(color.begin(), color.end(), '{'), color.end());
        color.erase(remove(color.begin(), color.end(), '}'), color.end());
        
        if (!color.empty()) {
            colors.pushback(color); 
        }
    }

    return Product(id, name, category, price, stock, description,colors, brand);
}

void DataController::saveCartData(const Cart& cart) {
    string folderPath = "Data/CartInformation";
    if (!filesystem::exists(folderPath)) {
        filesystem::create_directory(folderPath);
    }
    string filePath = folderPath + "/" + cart.getCustomerID() + "_cart.csv";
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "Không thể mở file để ghi: " << filePath << endl;
        return;
    }
    file << "Product Name,Product ID,Price,Quantity\n";
    const Vector<Pair<Product, int>>& cartItems = cart.getItems();
    for (long i = 0; i < cartItems.getSize(); ++i) {
        const Product& product = cartItems[i].getFirst();
        int quantity = cartItems[i].getSecond();
        file << product.getName() << ","
            << product.getProductId() << ","
            << product.getPrice() << ","
            << quantity << "\n";
    }
    file.close();
}

Cart DataController::loadCartData(const string& customerID) {
    Cart cart(customerID);
    string filePath = "Data/CartInformation/" + customerID + "_cart.csv";
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Không thể mở file để đọc: " << filePath << endl;
        return cart; 
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, id;
        double price = 0.0;
        int quantity = 0;
        
        getline(ss, name, ',');
        getline(ss, id, ',');

        if (!(ss >> price)) continue;  
        ss.ignore(); 

        if (!(ss >> quantity)) continue; 
        ss.ignore(); 

        
        if (!name.empty() && !id.empty() && quantity > 0) {
            Product product(id, name, "", price, 0, "", Vector<string>(), ""); 
            cart.addItem(product, quantity); 
        }
    }

    file.close();
    return cart;
}
