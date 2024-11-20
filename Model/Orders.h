#pragma once
#include <string>
#include "Datastructures/Vector.h"
#include "Model/Invoice.h"

using namespace std;

class SoldProduct;
class Orders {
private:
    string customerID;
    Vector<Invoice*> invoices;

public:
    Orders();
    Orders(const Orders& other);
    Orders(const string& customerId);
    void addInvoice(Invoice* invoice);
    string getCustomerID() const;
    void setCustomerID(const string& id);
    Vector<Invoice*> getInvoice() const;
    string displayOrders() const;

};
