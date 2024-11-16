#pragma once
#include "Model/Product.h"
#include "Model/Cart.h"
#include "Model/Invoice.h"
#include "Model/Orders.h"
#include "Model/Customer.h"
#include "Model/Employee.h"
#include "Model/Manager.h"
#include "Datastructures/Vector.h"
#include <vector>
#include <string>
using namespace std; 
class Customer;
class Employee;
class Manager;

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
    void print(const Vector<Employee>& Employees);
    bool findInvoiceByInvoiceID(const string& userID, const string& invoiceID , string& invoice);

    Vector<Customer> loadAllCustomersData();
    void saveAllCustomersData(const Vector<Customer>& customers);
    void addCustomer(const Customer& customer);
    void deleteCustomer(const Customer& customer);

    Vector<Employee> loadAllEmployeesData();
    void saveAllEmployeesData(const Vector<Employee>& Employees);
    void addEmployee(const Employee& Employee);
    void deleteEmployee(const Employee& Employee);

    Vector<Manager> loadAllManagersData();
    void saveAllManagersData(const Vector<Manager>& Managers);
    void addManager(const Manager& Manager);
    void deleteManager(const Manager& Manager);

    void testLoadDataAndPrint();

private:
    string invoicesFileName;
    string productFileName;
    Product parseProduct(const string& line);   
};

