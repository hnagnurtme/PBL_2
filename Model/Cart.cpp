#include "Model/Cart.h"
#include "Model/Product.h"
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"
#include <string>
#include <iostream>

using namespace std;

Cart::Cart(string id) : customerID(id) {}

void Cart::setCartID(string id) { customerID = id; }

Cart::Cart(const Cart& other) : customerID(other.customerID) { items = other.items; }

void Cart::addItem(Product* product, int quantity) {
    if (quantity <= 0) {
        cerr << "Quantity must be greater than 0." << endl;
        return;
    }
    for (int i = 0; i < items.getSize(); ++i) {
        if (items[i].getFirst()->getProductId() == product->getProductId()) {
            items[i].setSecond(items[i].getSecond() + quantity);
            return;
        }
    }
    items.pushback(Pair<Product*, int>(product, quantity));
}

void Cart::removeItem(string productId) {
    for (int i = 0; i < items.getSize(); ++i) {
        if (items[i].getFirst()->getProductId() == productId) {
            items.remove(i);
            return;
        }
    }
    cerr << "Product with ID " << productId << " not found in the cart." << endl;
}

void Cart::clearCart() {
    while (!items.isEmpty()) {
        items.popback();
    }
}

Vector<Pair<Product*, int>> Cart::getItems() const { return items; }

string Cart::getCustomerID() const { return customerID; }

bool Cart::contains(const string& productId) const {
    for (long i = 0; i < items.getSize(); ++i) {
        if (items[i].getFirst()->getProductId() == productId) {
            return true; 
        }
    }
    return false; 
}

void Cart::reduceItem(const string& productId, int quantity) {
    for (long i = 0; i < items.getSize(); ++i) {
        if (items[i].getFirst()->getProductId() == productId) {
            int currentQuantity = items[i].getSecond();
            if (currentQuantity > quantity) {
                items[i].setSecond(currentQuantity - quantity); 
            } else {
                items.remove(i); 
            }
            break; 
        }
    }
}

int Cart::getItemQuantity(const string& productId) const {
    for (long i = 0; i < items.getSize(); ++i) {
        if (items[i].getFirst()->getProductId() == productId) {
            return items[i].getSecond(); 
        }
    }
    return 0; 
}

bool Cart::isEmptyCart() {
    return items.isEmpty();
}

void Cart::addProductToCart(Product* product, int count){
    items.pushback(Pair<Product*, int>(const_cast<Product*>(product), count));
}