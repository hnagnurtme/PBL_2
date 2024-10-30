#pragma once
#include "Model/User.h"
#include "Model/Cart.h"
#include "Model/Orders.h"
#include "Datastructures/Vector.h"
#include <string>
using namespace std;
class Customer : public User {
private:
    Cart cart;
    Vector<Orders> orderHistory;

public:
    void viewCart() const;
    void addToCart(const Product& product, int quantity);
    void placeOrder();
    void viewOrderHistory() const;
};
