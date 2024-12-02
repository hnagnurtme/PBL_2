#pragma once
#include <string>
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"
#include "Model/Product.h"
#include "Model/Cart.h"
#include <mutex>

using namespace std;
class Product;
class Cart;
class Invoice {
private:
    string invoiceId;
    string customerId;
    Vector<Pair<Product*, int>> products;
    string invoiceDate;
    double totalAmount;
    string deliveryDate;
    string paymentMethod;

public:
    Invoice();
    Invoice(const Cart& cart);
    Invoice(const string& invoiceId, const string& customerId, const Vector<Pair<Product*, int>>& products, double totalAmount);
    
    string displayInvoice() const;

    string getInvoiceId() const;
    string getCustomerId() const;
    string getInvoiceDate() const;
    double getTotalAmount() const;
    Vector<Pair<Product*, int>> getProducts() const;
    string getDeliveryDate() ;
    string getPaymentMethod();
    string generateCounterID();

    void setInvoiceId(const string& id);
    void setCustomerId(const string& id);
    void setInvoiceDate();
    void setInvoiceDate(const string& date);
    void setTotalAmount(double amount);
    void setDeliveryDate(const string& deliveryDate);
    void setPaymentMethod(const string& paymentMethod);
    void setInvoiceID(int count);
    
    void  addProductToInvoice(Product* , int count);
};