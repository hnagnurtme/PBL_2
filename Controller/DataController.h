#pragma once
#include "Model/Product.h"
#include "Model/Cart.h"
#include "Model/Invoice.h"
#include "Model/Orders.h"
#include "Model/Customer.h"
#include "Datastructures/Vector.h"
#include <vector>
#include <string>
using namespace std; 

class DataController {
public:
    Product findProductById(const string& productId);
    void saveProductsData(const Vector<Product>& product);
    Vector<Product> loadProductData(); 
    void removeProduct(const Invoice &invoice);
    void saveCartData(const Cart& cart);       
    Cart loadCartData(const string& customerID);
    void saveInvoiceData(const Invoice& invoice);
    Invoice loadInvoiceData(const string& invoiceID, const string& customerID);
    void saveOrdersData(const Orders & orders);
    Orders loadOrdersData(const string& customerID);
    
    void printOrdersToFile(const Orders& orders);

private:
    string invoicesFileName;
    string productFileName;
    Product parseProduct(const string& line);   
};

