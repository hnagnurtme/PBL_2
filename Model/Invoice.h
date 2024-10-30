#pragma once
#include "Model/Product.h"
#include "Model/Order.h"
#include "Datastructures/Vector.h"
#include <string>
using namespace std;
class Invoice {
private:
    string invoiceId;
    string customerId;
    Order order;
    string invoiceDate;
    double totalAmount;

public:
    void displayInvoice() const;
};
