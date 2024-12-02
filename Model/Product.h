#pragma once
#include <string>
using namespace std;
#include "User.h"
#include "Model/Invoice.h"
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"

class Invoice;
class Cart;
class Product {

private:
    string productId;
    string name;
    string category;
    double price;
    int stock;
    string description;
    Vector<string> detail;
    string brand;
public:
    Product();
    Product(const Product&);
    Product(string id, const string& name, const string& category, double price, int stock,
            const string& description,const Vector<string>& detail, const string& brand);
    string getProductId() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    int getStock() const;
    string getDescription() const;
    Vector<string> getDetail() const;
    string getBrand() const;
    void setProductId(const string& newID);
    void setName(const string& newName);
    void setPrice(double newPrice);
    void setStock(int newStock);
    void setDescription(const string& newDescription);
    void setCategory(const string& newCategory);
    void setDetail(const Vector<string> & newDetail);
    void setBrand(const string& newBrand);
    void displayInfo() const;
    bool isAvailable(int requestedQuantity) const;
    bool isEmpty() const;
    Product& operator=(const Product& other);
};