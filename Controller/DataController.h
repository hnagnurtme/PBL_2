#pragma once
#include "Model/Product.h"
#include "Model/Cart.h"
#include  "Datastructures/Vector.h"
#include <vector>
#include <string>
using namespace std; 

class DataController {
public:
    Product findProductById(const string& productId);
    
    Vector<Product> loadProductData(); 
    void saveCartData(const Cart& cart);       
    Cart loadCartData(const string& customerID);
    void setProductFileName(const string& filename);
private:
    string invoicesFileName;
    string cartFileName;
    string productFileName;
    Product parseProduct(const string& line);
};

