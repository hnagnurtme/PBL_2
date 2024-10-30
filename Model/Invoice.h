#pragma once
#include <string>
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"
#include "Model/Product.h"
#include "Model/Cart.h"

using namespace std;

class Invoice {
private:
    string invoiceId;
    string customerId;
    Vector<Pair<Product, int>> products;
    string invoiceDate;
    double totalAmount;
    string deliveryDate;
    string paymentMethod;

public:
    Invoice();
    Invoice(const Cart& cart);
    Invoice(const string& invoiceId, const string& customerId, const Vector<Pair<Product, int>>& products, double totalAmount);
    
    string displayInvoice() const;
    
    string getInvoiceId() const;
    void setInvoiceId(const string& id);
    
    string getCustomerId() const;
    void setCustomerId(const string& id);
    
    void setInvoiceDate();
    string getInvoiceDate() const;

    void setTotalAmount(double amount);
    double getTotalAmount() const;

    void setDeliveryDate(const string& deliveryDate);
    void setPaymentMethod(const string& paymentMethod);
};
