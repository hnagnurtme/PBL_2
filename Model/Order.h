#pragma once
#include <string>
using namespace std;
#include "User.h"
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"
#include "Model/Product.h"

class Order {
private:
    string orderId;
    Vector<Pair<Product, int>> items;
    string orderDate;
    string deliveryDate;
    string paymentMethod;

public:
    void showOrderDetails() const;
};
