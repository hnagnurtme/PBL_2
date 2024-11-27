#include "Controller/DataController.h"
#include "Datastructures/Vector.h"
#include <unordered_map>
#include "Datastructures/Pair.h"
#include "Model/Product.h"
#include "Model/Customer.h"
#include "Model/Employee.h"
#include "Model/Manager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <stdexcept>
using namespace std;

void ensureFileAndFolder(const string& folderPath, const string& filename, const string& header) {
    if (!std::filesystem::exists(folderPath)) {
        std::filesystem::create_directories(folderPath);
    }

    if (!std::filesystem::exists(filename)) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Không thể tạo file: " + filename);
        }
        file << header << "\n";
        file.close();
    }
}
template <typename T>
void saveAllData(const Vector<T>& items, const std::string& filename, 
                    function<std::string(const T&)> serializeItem) {
    const std::string header = "UserID;Name;Email;Phone;Password;Address";

    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Không thể mở file để ghi: " + filename);
    }

    file << header << "\n";
    for (int i = 0; i < items.getSize(); ++i) {
        file << serializeItem(items[i]) << "\n";
    }
    file.close();
}

template <typename T>
Vector<T> loadAllData(
    const string& filename,
    function<T(const string&, const string&, const string&, const string&, const string&, const string&)> createObject
) {
    const std::string header = "UserID;Name;Email;Phone;Password;Address";
    ensureFileAndFolder("Data", filename, header);

    Vector<T> items;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Không thể mở file để đọc: " + filename);
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string userId, name, email, phone, password, address;

        getline(ss, userId, ';');
        getline(ss, name, ';');
        getline(ss, email, ';');
        getline(ss, phone, ';');
        getline(ss, password, ';');
        getline(ss, address);

        items.pushback(createObject(userId, name, email, phone, password, address));
    }

    return items;
}

void DataController::saveProductsData(const Vector<Product>& products) {
    const string newProductFileName = "Data/ProductInformation.csv"; 
    ofstream tempFile(newProductFileName, ios::out | ios::trunc);
    if (!tempFile.is_open()) {
        throw runtime_error("Không thể mở file để ghi: " + newProductFileName);
    }

    for (int i = 0; i < products.getSize(); ++i) {
        const Product& product = products[i];
        
        tempFile << product.getProductId() << ";"
                << product.getName() << ";"
                << product.getCategory() << ";"
                << product.getPrice() << ";"
                << product.getStock() << ";"
                << product.getDescription() << ";";

        Vector<string> detail = product.getDetail();
        tempFile << "{";
        for (int j = 0; j < detail.getSize(); ++j) {
            tempFile << detail[j];
            if (j < detail.getSize() - 1) {
                tempFile << ",";
            }
        }
        tempFile << "};";
        tempFile << product.getBrand() << "\n";
    }
    tempFile.close();
}

Vector<Product> DataController::loadProductData() {
    Vector<Product> products;
    ifstream file("Data/ProductInformation.csv");

    cout << "Trying to open file: " << productFileName << endl; 

    if (!file.is_open()) {
        throw runtime_error("Không thể mở file: " + productFileName);
    }

    string line;
    while (getline(file, line)) {
        Product product = parseProduct(line);
        products.pushback(product); 
    }

    file.close();
    return products;
}

Product DataController::parseProduct(const string& line) {
    istringstream ss(line);
    string id, name, category, priceStr, stockStr, description, sizesStr, detailStr, brand;

    getline(ss, id, ';');         
    getline(ss, name, ';');
    getline(ss, category, ';');
    getline(ss, priceStr, ';');
    getline(ss, stockStr, ';');
    getline(ss, description, ';');
    getline(ss, detailStr, ';');
    getline(ss, brand, ';');

    double price = stod(priceStr);
    int stock = stoi(stockStr);

    Vector<string> details;
    istringstream detailsStream(detailStr);
    string detail;

    while (getline(detailsStream, detail, ',')) {
        detail.erase(remove(detail.begin(), detail.end(), '{'), detail.end());
        detail.erase(remove(detail.begin(), detail.end(), '}'), detail.end());
        
        if (!detail.empty()) {
            details.pushback(detail); 
        }
    }

    return Product(id, name, category, price, stock, description,details, brand);
}


void DataController::deleteProduct(const string& productId) {
    Vector<Product> productList = loadProductData();
    for (int j = 0; j < productList.getSize(); ++j) {
        if (productList[j].getProductId() == productId) {
            productList.remove(j);  
            saveProductsData(productList);
            return;
        }
    }
    throw runtime_error("Không tìm thấy product với ProductId: " + productId); 
}
void DataController::removeProduct(const Invoice &invoice) {
    Vector<Pair<Product*, int>> invoiceProducts = invoice.getProducts();
    Vector<Product> productList = loadProductData(); 

    for (int i = 0; i < invoiceProducts.getSize(); ++i) {
        const string& productId = invoiceProducts[i].getFirst()->getProductId();
        int quantityToRemove = invoiceProducts[i].getSecond();

        for (int j = 0; j < productList.getSize(); ++j) {
            if (productList[j].getProductId() == productId) {
                int currentStock = productList[j].getStock();
                if (currentStock <= quantityToRemove) {
                    productList.remove(j); 
                    --j; 
                } else {
                    productList[j].setStock(currentStock - quantityToRemove);
                }
                break; 
            }
        }
    }
    saveProductsData(productList); 
}

void DataController::saveCartData(const Cart& cart) {
    string folderPath = "Data/CartInformation";
    if (!filesystem::exists(folderPath)) {
        filesystem::create_directory(folderPath);
    }
    string filePath = folderPath + "/" + cart.getCustomerID() + "_cart.csv";
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "Không thể mở file để ghi: " << filePath << endl;
        return;
    }
    file << "Product Name,Product ID,Price,Quantity\n";
    const Vector<Pair<Product*, int>>& cartItems = cart.getItems();
    for (long i = 0; i < cartItems.getSize(); ++i) {
        const Product* product = cartItems[i].getFirst();
        int quantity = cartItems[i].getSecond();
        file << product->getName() << ","
            << product->getProductId() << ","
            << product->getPrice() << ","
            << quantity << "\n";
    }
    file.close();
}

Invoice DataController::loadInvoiceData(const string& invoiceID) {
    string directory = "Data/InvoiceInformation";
    string filename = directory + "/"  + "_Invoice_" + invoiceID + ".txt"; 

    Invoice invoice;

    ifstream inFile(filename); 

    if (inFile.is_open()) {
        string line;

        getline(inFile, line);
        invoice.setInvoiceId(line.substr(12));

        getline(inFile, line);
        invoice.setCustomerId(line.substr(14));

        getline(inFile, line);
        invoice.setInvoiceDate(line.substr(14));

        getline(inFile, line);
        invoice.setDeliveryDate(line.substr(15));

        getline(inFile, line);
        invoice.setPaymentMethod(line.substr(16));

        getline(inFile, line);
        invoice.setTotalAmount(stod(line.substr(14)));

        while (getline(inFile, line)) {
            if (line.empty()) break;

            stringstream ss(line);
            string productName, productId;
            double price = 0.0;
            int quantity = 0;
            
            getline(ss, productName, ',');  
            getline(ss, productId, ',');   

            if (!(ss >> price)) continue;  
            ss.ignore();  

            if (!(ss >> quantity)) continue; 
            ss.ignore(); 

            if (!productName.empty() && !productId.empty() && quantity > 0) {
                Product* product = new Product(productId, productName, "", price, 0, "", Vector<string>(), "");
                invoice.addProductToInvoice(product, quantity);
            }
        }

        inFile.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }

    return invoice;
}

void DataController::saveInvoiceData(const Invoice& invoice) {
    string directory = "Data/InvoiceInformation";
    string filename = directory + "/" + "_Invoice_" + invoice.getInvoiceId() + ".txt"; 

    filesystem::create_directories(directory);

    ofstream outFile(filename); 

    if (outFile.is_open()) {
        outFile << invoice.displayInvoice(); 
        outFile.close(); 
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void DataController::saveOrdersData(const Orders& orders) {
    string directory = "Data/OrdersInfomation";
    string filename = directory + "/" + orders.getCustomerID() + ".csv";
    
    filesystem::create_directories(directory);

    ofstream outFile(filename);  

    Vector<Invoice*> newInvoices = orders.getInvoice();
    
    if (outFile.is_open()) {
        outFile << "InvoiceID,PlaceOrderDate,DeliveryDate,TotalAmount,PaymentMethod\n";

        for (int i = 0; i < newInvoices.getSize(); i++) {
            string invoiceID = newInvoices[i]->getInvoiceId();
            string invoiceDate = newInvoices[i]->getInvoiceDate();
            string invoiceDeliveryDate = newInvoices[i]->getDeliveryDate();
            double invoiceTotalAmount = newInvoices[i]->getTotalAmount();
            string invoicePaymentMethod = newInvoices[i]->getPaymentMethod();
            
            outFile << invoiceID << ","
                    << invoiceDate << ","
                    << invoiceDeliveryDate << ","
                    << invoiceTotalAmount << ","
                    << invoicePaymentMethod << "\n";
        }
        
        outFile.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

Orders DataController::loadOrdersData(const string& customerID) {
    string directory = "Data/OrdersInfomation";
    string filename = directory + "/" + customerID + ".csv";

    Orders orders(customerID); 

    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Unable to open file for reading." << endl;
        return orders; 
    }

    string line;
    getline(inFile, line);  

    while (getline(inFile, line)) {
        stringstream ss(line);
        string invoiceID, invoiceDate, invoiceDeliveryDate, paymentMethod;
        double totalAmount;

        getline(ss, invoiceID, ',');
        getline(ss, invoiceDate, ',');
        getline(ss, invoiceDeliveryDate, ',');

        string totalAmountStr;
        getline(ss, totalAmountStr, ',');
        totalAmount = stod(totalAmountStr);

        getline(ss, paymentMethod, ',');

        Invoice* invoice = new Invoice();
        invoice->setInvoiceId(invoiceID);
        invoice->setInvoiceDate(invoiceDate);
        invoice->setDeliveryDate(invoiceDeliveryDate);
        invoice->setTotalAmount(totalAmount);
        invoice->setPaymentMethod(paymentMethod);

        orders.addInvoice(invoice);
    }

    inFile.close();
    return orders; 
}

Cart DataController::loadCartData(const string& customerID) {
    Cart cart(customerID);
    string filePath = "Data/CartInformation/" + customerID + "_cart.csv";
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Không thể mở file để đọc: " << filePath << endl;
        return cart; 
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, id;
        double price = 0.0;
        int quantity = 0;
        
        getline(ss, name, ',');
        getline(ss, id, ',');

        if (!(ss >> price)) continue;  
        ss.ignore(); 

        if (!(ss >> quantity)) continue; 
        ss.ignore(); 

        if (!name.empty() && !id.empty() && quantity > 0) {
            Product *product = new Product(id, name, "", price, 0, "", Vector<string>(), ""); 
            cart.addItem(product, quantity); 
        }
    }

    file.close();
    return cart;
}

bool DataController::findInvoiceByInvoiceID( const string& invoiceID, string& invoice) {
    std::string filename = "Data/InvoiceInformation/";
    filename.append("_Invoice_").append(invoiceID).append(".txt");

    cout << "Looking for file: " << filename << endl;
    ifstream inFile(filename);
    if (!inFile) {
        cout << "File does not exist or unable to open: " << filename << endl;
        return false;
    }
    stringstream buffer;
    buffer << inFile.rdbuf();
    invoice = buffer.str();

    inFile.close();
    return true;
}

Vector<Customer> DataController::loadAllCustomersData() {
    const std::string filename = "Data/CustomerInformation.csv";

    return loadAllData<Customer>(
        filename,
        [](const std::string& userId, const std::string& name, const std::string& email,
           const std::string& phone, const std::string& password, const std::string& address) {
            return Customer(userId, name, email, phone, password, address);
        }
    );
}

void DataController::saveAllCustomersData(const Vector<Customer>& customers) {
    const std::string filename = "Data/CustomerInformation.csv";

    saveAllData<Customer>(
        customers, 
        filename, 
        [](const Customer& customer) {
            return customer.getUserId() + ";" + 
                   customer.getName() + ";" + 
                   customer.getEmail() + ";" + 
                   customer.getPhone() + ";" + 
                   customer.getPassword() + ";" + 
                   customer.getAddress();
        }
    );
}

void DataController::addCustomer(const Customer& customer) {
    Vector<Customer> customers = loadAllCustomersData();
    customers.pushback(customer);
    saveAllCustomersData(customers);
}

void DataController::deleteCustomer(const string& customerID) {
    Vector<Customer> customers = loadAllCustomersData();
    for (int i = 0; i < customers.getSize(); ++i) {
        if (customers[i].getUserId() == customerID) {
            customers.remove(i);
            saveAllCustomersData(customers);
            return;
        }
    }
    throw runtime_error("Không tìm thấy customer với UserID: " + customerID);
}

Customer DataController:: findCustomerById(const string& customerID){
    Vector<Customer> customers = loadAllCustomersData();
    for (int i = 0; i < customers.getSize(); ++i) {
        if (customers[i].getUserId() == customerID) {
            return customers[i];
            }
        }
    throw runtime_error("Không tìm thấy nhân viên với ID: " + customerID);
}

void DataController:: updateCustomer(const Customer& customer){
    string id = customer.getUserId();
    deleteCustomer(id);
    addCustomer(customer);
}

Manager DataController::  findManagerById(const string& managerID){
    Vector<Manager> managers = loadAllManagersData();
    for (int i = 0; i < managers.getSize(); ++i) {
        if (managers[i].getUserId() == managerID) {
            return managers[i];
            }
            }
}

Vector<Employee> DataController::loadAllEmployeesData() {
    const std::string filename = "Data/EmployeeInformation.csv";
    return loadAllData<Employee>(
        filename,
        [](const std::string& userId, const std::string& name, const std::string& email,
           const std::string& phone, const std::string& password, const std::string& address) {
            return Employee(userId, name, email, phone, password, address);
        }
    );
}

void DataController::saveAllEmployeesData(const Vector<Employee>& employees) {
const std::string filename = "Data/EmployeeInformation.csv";
saveAllData<Employee>(
    employees,
    filename,
    [](const Employee& employee) { 
        return employee.getUserId() + ";" +
               employee.getName() + ";" +
               employee.getEmail() + ";" +
               employee.getPhone() + ";" + 
               employee.getPassword() + ";" +
               employee.getAddress();
    }
);
}

void DataController::addEmployee(const Employee& employee) {
    Vector<Employee> employees = loadAllEmployeesData();
    employees.pushback(employee);
    saveAllEmployeesData(employees);
}

void DataController::deleteEmployee(const Employee& employee) {
    Vector<Employee> employees = loadAllEmployeesData();
    for (int i = 0; i < employees.getSize(); ++i) {
        if (employees[i].getUserId() == employee.getUserId()) {
            employees.remove(i);
            saveAllEmployeesData(employees);
            return;
        }
    }
    throw runtime_error("Không tìm thấy customer với UserID: " + employee.getUserId());
}

Vector<Manager> DataController::loadAllManagersData() {
    const string filename = "Data/ManagerInformation.csv";
    return loadAllData<Manager>(
        filename,
        [](const std::string& userId, const std::string& name, const std::string& email,
           const std::string& phone, const std::string& password, const std::string& address) {
            return Manager(userId, name, email, phone, password, address);
        }
    );
}

void DataController::saveAllManagersData(const Vector<Manager>& managers) {
    const std::string filename = "Data/ManagerInformation.csv";
saveAllData<Manager>(
    managers,
    filename,
    [](const Manager& manager) {
        return manager.getUserId() + ";" +
               manager.getName() + ";" +
               manager.getEmail() + ";" +
               manager.getPhone() + ";" +
               manager.getPassword() + ";" +
               manager.getAddress();
    }
);   
}

void DataController::addManager(const Manager& manager) {
    Vector<Manager> managers = loadAllManagersData();
    managers.pushback(manager);
    saveAllManagersData(managers);
}

void DataController::deleteManager(const Manager& manager) {
    Vector<Manager> managers = loadAllManagersData();
    for (int i = 0; i < managers.getSize(); ++i) {
        if (managers[i].getUserId() == manager.getUserId()) {
            managers.remove(i);
            saveAllManagersData(managers);
            return;
        }
    }
    throw runtime_error("Không tìm thấy customer với UserID: " + manager.getUserId());
}

void DataController::addToSoldProductData(const Invoice& invoice) {
    const string soldProductFileName = "Data/AllSoldProduct.csv";
    Vector<Pair<string, int>> soldProducts = loadSoldProductData();
    Vector<Pair<Product*, int>> invoiceProducts = invoice.getProducts();

    for (int i = 0; i < invoiceProducts.getSize(); ++i) {
        Product* product = invoiceProducts[i].getFirst();
        string productId = product->getProductId();
        int quantity = invoiceProducts[i].getSecond();

        bool found = false;
        for (int j = 0; j < soldProducts.getSize(); ++j) {
            if (soldProducts[j].getFirst() == productId) {
                soldProducts[j].setSecond(soldProducts[j].getSecond() + quantity);
                found = true;
                break;
            }
        }
        if (!found) {
            soldProducts.pushback(Pair<string,int>(productId, quantity));
        }
    }

    ofstream outputFile(soldProductFileName, ios::out | ios::trunc);
    if (!outputFile.is_open()) {
        throw runtime_error("Không thể mở file để ghi: " + soldProductFileName);
    }

    outputFile << "ProductID,Quantity\n";
    for (int i = 0; i < soldProducts.getSize(); ++i) {
        outputFile << soldProducts[i].getFirst() << "," << soldProducts[i].getSecond() << "\n";
    }

    outputFile.close();
}

Vector<Pair<string, int>> DataController::loadSoldProductData() {
    const string soldProductFileName = "Data/AllSoldProduct.csv";
    ifstream inputFile(soldProductFileName);

    if (!inputFile.is_open()) {
        ofstream outputFile(soldProductFileName, ios::out);
        if (!outputFile.is_open()) {
            throw runtime_error("Không thể tạo file: " + soldProductFileName);
        }
        outputFile << "ProductID,Quantity\n";
        outputFile.close();
        return {};
    }

    Vector<Pair<string, int>> soldProducts;
    string line;

    if (!getline(inputFile, line)) {
        inputFile.close();
        throw runtime_error("File rỗng hoặc không đúng định dạng: " + soldProductFileName);
    }

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string productId;
        string quantityStr;

        if (!getline(iss, productId, ',') || !getline(iss, quantityStr)) {
            continue;
        }

        int quantity = stoi(quantityStr);
        soldProducts.pushback(Pair<string, int>(productId, quantity));
    }

    inputFile.close();
    return soldProducts;
}

Product DataController:: findProductById(const string& productId){
    Vector<Product> products = loadProductData();
    for( int i = 0; i < products.getSize();i++){
        if(products[i].getProductId() == productId){
            return products[i];
    }
    }
    return Product();
}


