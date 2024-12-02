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
    void setInvoiceId(const string& id);
    
    string getCustomerId() const;
    void setCustomerId(const string& id);
    
    void setInvoiceDate();
    void setInvoiceDate(const string& date);
    string getInvoiceDate() const;

    void setTotalAmount(double amount);
    double getTotalAmount() const;

    Vector<Pair<Product*, int>> getProducts() const;

    void setDeliveryDate(const string& deliveryDate);
    string getDeliveryDate() ;
    void setPaymentMethod(const string& paymentMethod);
    string getPaymentMethod();

    void  addProductToInvoice(Product* , int count);

    void setInvoiceID(int count);
    string generateCounterID();
};