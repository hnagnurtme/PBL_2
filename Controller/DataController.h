#pragma once
#include "Model/Product.h"
#include "Model/Cart.h"
#include "Model/Invoice.h"
#include  "Datastructures/Vector.h"
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
private:
    string invoicesFileName;
    string productFileName;
    Product parseProduct(const string& line);   
};

