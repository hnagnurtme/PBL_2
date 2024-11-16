#include "Controller/DataController.h"
#include "Datastructures/Vector.h"
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

void DataController::saveProductsData(const Vector<Product>& products) {
    const string newProductFileName = "D:\\NEWPBL\\Data\\ProductInformation.csv"; 
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
    ifstream file("D:\\NEWPBL\\Data\\ProductInformation.csv");

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

Invoice DataController::loadInvoiceData(const string& invoiceID, const string& customerID) {
    string directory = "Data/InvoiceInformation";
    string filename = directory + "/" + customerID + "_Invoice_" + invoiceID + ".txt"; 

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
    string filename = directory + "/" + invoice.getCustomerId() + "_Invoice_" + invoice.getInvoiceId() + ".txt"; 

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

void DataController::printOrdersToFile(const Orders& orders) {
    string tempFilename = "Data/OrdersInfomation/temp_orders_output.csv";
    ofstream outFile(tempFilename);

    if (outFile.is_open()) {
        outFile << "InvoiceID,PlaceOrderDate,DeliveryDate,TotalAmount,PaymentMethod,Products\n";  // Tiêu đề file CSV

        Vector<Invoice*> invoices = orders.getInvoice();
        for (int i = 0; i < invoices.getSize(); i++) {
            Invoice* invoice = invoices[i];
            outFile << invoice->getInvoiceId() << ","
                    << invoice->getInvoiceDate() << ","
                    << invoice->getDeliveryDate() << ","
                    << invoice->getTotalAmount() << ","
                    << invoice->getPaymentMethod() << ",";

            Vector<Pair<Product*, int>> products = invoice->getProducts();
            outFile << "{";
            for (int j = 0; j < products.getSize(); j++) {
                outFile << "(";
                outFile << products[j].getFirst()->getProductId(); // Sửa từ products[i] thành products[j]
                outFile << "," << products[j].getSecond(); // Thêm dấu phẩy giữa ID sản phẩm và số lượng
                outFile << ")";
                if (j < products.getSize() - 1) {
                    outFile << ","; // Thêm dấu phẩy chỉ giữa các sản phẩm, không phải sau sản phẩm cuối
                }
            }
            outFile << "},";
            outFile << "\n"; // Xuống dòng sau mỗi hóa đơn
        }
        outFile.close();
        cout << "Orders data has been written to temp_orders_output.csv for verification." << endl;
    } 
    else {
        cout << "Unable to open file for writing." << endl;
    }
}

bool DataController::findInvoiceByInvoiceID(const string& userID, const string& invoiceID, string& invoice) {
    string filename = "Data/InvoiceInformation/" + userID + "_Invoice_" + invoiceID + ".txt";
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

// Hàm đọc dữ liệu của khách hàng
Vector<Customer> DataController::loadAllCustomersData() {
    const string filename = "Data/CustomerInformation.csv";
    const string header = "UserID;Name;Email;Phone;Password;Address";
    ensureFileAndFolder("Data", filename, header);
    
    Vector<Customer> customers;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Không thể mở file để đọc: " + filename);
    }

    std::string line;
    std::getline(file, line);  // Bỏ qua dòng tiêu đề
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string userId, name, email, phone, password, address;

        std::getline(ss, userId, ';');
        std::getline(ss, name, ';');
        std::getline(ss, email, ';');
        std::getline(ss, phone, ';');
        std::getline(ss, password, ';');
        std::getline(ss, address);

        Customer *newCus = new Customer(userId, name, email, phone, password, address);
        // Tạo đối tượng Customer và thêm vào Vector
        customers.pushback(*newCus);
    }

    return customers;
}

// Hàm ghi dữ liệu khách hàng
void DataController::saveAllCustomersData(const Vector<Customer>& customers) {
    const string filename = "Data/CustomerInformation.csv";
    const string header = "UserID;Name;Email;Phone;Password;Address";
    ofstream file(filename, ios::out | ios::trunc);
    if (!file.is_open()) {
        throw runtime_error("Không thể mở file để ghi: " + filename);
    }

    file << header << "\n";
    for (int i = 0; i < customers.getSize(); ++i) {
        const Customer& customer = customers[i];
        file << customer.getUserId() << ";"
             << customer.getName() << ";"
             << customer.getEmail() << ";"
             << customer.getPhone() << ";"
             << customer.getPassword() << ";"
             << customer.getAddress() << "\n";
    }
    file.close();
}

// Hàm thêm khách hàng
void DataController::addCustomer(const Customer& customer) {
    Vector<Customer> customers = loadAllCustomersData();
    customers.pushback(customer);
    saveAllCustomersData(customers);
}

// Hàm xóa khách hàng
void DataController::deleteCustomer(const Customer& customer) {
    Vector<Customer> customers = loadAllCustomersData();
    for (int i = 0; i < customers.getSize(); ++i) {
        if (customers[i].getUserId() == customer.getUserId()) {
            customers.remove(i);
            saveAllCustomersData(customers);
            return;
        }
    }
    throw runtime_error("Không tìm thấy customer với UserID: " + customer.getUserId());
}


// Hàm dành riêng cho Employee
Vector<Employee> DataController::loadAllEmployeesData() {
    
    
}

void DataController::saveAllEmployeesData(const Vector<Employee>& employees) {
   
}

void DataController::addEmployee(const Employee& employee) {
   
}

void DataController::deleteEmployee(const Employee& employee) {
   
}


Vector<Manager> DataController::loadAllManagersData() {
   
}

void DataController::saveAllManagersData(const Vector<Manager>& managers) {
    
}

void DataController::addManager(const Manager& manager) {
    
}

void DataController::deleteManager(const Manager& manager) {
    
}
void DataController::testLoadDataAndPrint() {
    try {
        // Tạo đối tượng DataController
        DataController dataController;

        // Load dữ liệu khách hàng từ file
        Vector<Customer> customers = dataController.loadAllCustomersData(); // Gọi từ đối tượng

        // Đường dẫn tới file tạm
        const std::string tempFilename = "temp_customer_data_output.csv";

        // Mở file tạm để ghi
        std::ofstream outFile(tempFilename);
        if (!outFile.is_open()) {
            throw std::runtime_error("Không thể mở file tạm: " + tempFilename);
        }

        // Ghi dữ liệu vào file tạm
        outFile << "UserID,Name,Email,Phone,Password,Address\n"; // Tiêu đề
        for (int i = 0; i < customers.getSize(); ++i) {
            const Customer& customer = customers[i];
            outFile << customer.getUserId() << ","
                    << customer.getName() << ","
                    << customer.getEmail() << ","
                    << customer.getPhone() << ","
                    << customer.getPassword() << ","
                    << customer.getAddress() << "\n";
        }

        outFile.close(); // Đóng file
        std::cout << "Dữ liệu đã được ghi vào file tạm: " << tempFilename << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Lỗi: " << ex.what() << std::endl;
    }
}

