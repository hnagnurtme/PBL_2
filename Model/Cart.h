#pragma once
#include "Model/User.h"
#include "Model/Product.h"
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"
#include <string>
#include <iostream>
using namespace std;
class Product;
class Cart {
private:
    Vector<Pair<Product*, int>> items;
    string customerID;
public:
    Cart(string id ="");
    Cart(const Cart&);

    void setCartID(string id);
    void addItem(Product* product, int quantity);
    void reduceItem(const string& productId, int quantity);
    void removeItem(string productId);
    void clearCart();

    Vector<Pair<Product*, int>> getItems() const;
    string getCustomerID() const;
    int getItemQuantity(const string& productId) const;
    
    bool contains(const string& productId) const;
    bool isEmptyCart();

    void addProductToCart(Product* , int count);
};