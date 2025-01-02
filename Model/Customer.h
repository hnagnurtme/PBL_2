#pragma once
#include "Model/User.h"
#include "Model/Cart.h"
#include "Model/Orders.h"
#include "Model/Invoice.h"
#include "Datastructures/Vector.h"
#include "Controller/DataController.h"
#include <string>
using namespace std;
class Customer : public User {
private:
    Cart *cart;
    Orders *orderHistory;
public:
    Customer(const string& userId ="");
    Customer(const Customer&);
    Customer(const string& id, const string& name, const string& email, const string& phone, const string& password, const string& address);
    ~Customer();
    
    void addToCart(Product* product, int quantity);
    void reduceItem(const string& productId, int quantity);
    void removeItem(string productId);
    void payment(const string& deliveryDate,const string& paymentMethod);
    Cart*  getCart() const;
    Orders& getOrderHistory() const;
    void updateOrderHistory(const Orders& newOrderHistory);
    Customer& operator=(const Customer& other);
};