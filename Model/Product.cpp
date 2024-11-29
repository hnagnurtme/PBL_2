#include "Model/Product.h"
#include <iostream>
Product::Product() 
    : productId(""), name(""), category(""), price(0.0), stock(0), description(""), detail(), brand("") {}
Product :: Product (const Product& other){
    productId = other.productId;
    name = other.name;
    category = other.category;
    price = other.price;
    stock = other.stock;
    description = other.description;
    detail = other.detail;
    brand = other.brand;
}

Product::Product(string id, const string& name, const string& category, double price, int stock,
                const string& description, const Vector<string>& detail, const string& brand)
    : productId(id), name(name), category(category), price(price), stock(stock),
    description(description), detail(detail), brand(brand) {}

string Product::getProductId() const {
    return productId;
}

string Product::getName() const {
    return name;
}

string Product::getCategory() const {
    return category;
}

double Product::getPrice() const {
    return price;
}

int Product::getStock() const {
    return stock;
}

string Product::getDescription() const {
    return description;
}

Vector<string> Product::getDetail() const {
    return detail;
}

string Product::getBrand() const {
    return brand;
}
void Product::setProductId(const string& newID){
    productId = newID;
}
void Product::setName(const string& newName) {
    name = newName;
}

void Product::setPrice(double newPrice) {
    price = newPrice;
}

void Product::setStock(int newStock) {
    stock = newStock;
}

void Product::setDescription(const string& newDescription) {
    description = newDescription;
}

void  Product::setCategory(const string& newCategory){
    category = newCategory;
}
void  Product::setDetail(const Vector<string> & newDetail){
    detail = newDetail;
}
void  Product::setBrand(const string& newBrand){
    brand = newBrand;
}

void Product::displayInfo() const {
    cout << "Product ID: " << productId << endl;
    cout << "Name: " << name << endl;
    cout << "Category: " << category << endl;
    cout << "Price: $" << price << endl;
    cout << "Stock: " << stock << endl;
    cout << "Description: " << description << endl;
    cout << endl;
    cout << "Colors: ";
    for (long i = 0; i < detail.getSize(); ++i) {
        cout << detail[i] << " ";
    }
    cout << endl;
    cout << "Brand: " << brand << endl;
}

bool Product::isAvailable(int requestedQuantity) const {
    return requestedQuantity <= stock;
}

bool Product:: isEmpty() const {
        return productId.empty() || name.empty() || category.empty() ||
               price == 0.0 || stock == 0 || description.empty() || brand.empty();
    }

Product&  Product:: operator=(const Product& other) {
        if (this != &other) {  
            productId = other.productId;
            name = other.name;
            category = other.category;
            price = other.price;
            stock = other.stock;
            description = other.description;
            detail = other.detail;  
            brand = other.brand;
        }
        return *this;
    }