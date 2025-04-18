#pragma once
#include "Model/Product.h"
#include "Model/Cart.h"
#include "Model/Invoice.h"
#include "Model/Orders.h"
#include "Model/Customer.h"
#include "Model/Manager.h"
#include "Datastructures/Vector.h"
#include <string>
using namespace std; 
class Customer;
class Manager;

class DataController {
public:
    Product findProductById(const string& productId);
    void saveProductsData(const Vector<Product>& product);
    Vector<Product> loadProductData(); 
    void removeProduct(const Invoice &invoice);
    void deleteProduct(const string& productId);
    void addNewProduct(const Product& product);

    void saveCartData(const Cart& cart);       
    Cart loadCartData(const string& customerID);
    void saveInvoiceData(const Invoice& invoice);
    
    Vector<Pair<string, int>> loadSoldProductData();
    void saveOrdersData(const Orders & orders);
    Orders loadOrdersData(const string& customerID);

    void addToSoldProductData(const Invoice&invoice);
    Invoice loadInvoiceData(const string& invoiceID);
    bool findInvoiceByInvoiceID(const string& invoiceID , string& invoice);

    Vector<Customer> loadAllCustomersData();
    void saveAllCustomersData(const Vector<Customer>& customers);
    void addCustomer(const Customer& customer);
    void deleteCustomer(const string& customerID);
    Customer findCustomerById(const string& customerID);
    void updateCustomer(const Customer& customer);
    
    Vector<Manager> loadAllManagersData();
    void saveAllManagersData(const Vector<Manager>&);
    void addManager(const Manager& );
    void deleteManager(const string& );
    Manager findManagerById(const string& );
    void updateManager(const Manager&);
    
private:
    Product parseProduct(const string& line);   
};