#pragma once
#include "Model/User.h"
#include "Model/Cart.h"
#include "Model/Manager.h"
#include "Datastructures/Vector.h"
#include <string>
using namespace std;
class Customer : public User {
private:
    Cart cart;
    Vector<Order> orderHistory;

public:
    void viewCart() const;
    void addToCart(const Product& product, int quantity);
    void placeOrder();
    void viewOrderHistory() const;
};
