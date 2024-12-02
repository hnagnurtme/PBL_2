#include "Controller/AppController.h"
Pair<string, string> AppController::allLogin(const string& email, const string& password) {
    Vector<string> role = {"Customer", "Manager"};
    string userId;
    if ((userId = login(email, password, role[0])) != "Invalid") {
        return Pair<string, string>(role[0], userId);
    }
    else if ((userId = login(email, password, role[1])) != "Invalid") {
        return Pair<string, string>(role[1], userId);
    }
    return Pair<string, string>("Invalid", "Invalid");
}

string AppController::login(const string& email, const string& password, const string& role) {
    if (role == "Customer") {
        DataController data;
        Vector<Customer> allCustomer = data.loadAllCustomersData();
        for (int i = 0; i < allCustomer.getSize(); i++) {
            if (allCustomer[i].getEmail() == email && allCustomer[i].getPassword() == password) {
                return allCustomer[i].getUserId();
            }
        }
        return "Invalid";
    }
    else if (role == "Manager") {
        DataController data;
        Vector<Manager> allManagers = data.loadAllManagersData();
        for (int i = 0; i < allManagers.getSize(); i++) {
            if (allManagers[i].getEmail() == email && allManagers[i].getPassword() == password) {
                return allManagers[i].getUserId();
            }
        }
        return "Invalid";
    }
    return "Invalid";
}

string AppController::signin(const string& name, const string& email, const string& phone, const string& password, const string& address, const string& role) {
    string id;
    DataController* data = new DataController();  

    if (role == "Customer") {
        Vector<Customer> allCustomers = data->loadAllCustomersData();
        id = "USER"+ to_string(allCustomers.getSize() + 1);
        Customer *newCustomer = new Customer(id, name, email, phone, password, address);
        data->addCustomer(*newCustomer);  
    } 
    else if (role == "Manager") {
        Vector<Manager> allManagers = data->loadAllManagersData();
        id ="USER"+  to_string(allManagers.getSize() + 1);
        Manager *newManager = new Manager(id, name, email, phone, password, address);
        data->addManager(*newManager);  
    }
    else {
        delete data;  
        return "Vai trò không hợp lệ";
    }

    delete data; 
    return id;  
}

Vector<Invoice*> AppController::sortInvoiceByDate() {
    DataController* customerData = new DataController();
    Vector<Customer> customers = customerData->loadAllCustomersData();
    Vector<Invoice*> allInvoices;
    for (int i = 0; i < customers.getSize(); ++i) {
        Vector<Invoice*> invoices = customerData->loadOrdersData(customers[i].getUserId()).getInvoice();
        for (int j = 0; j < invoices.getSize(); ++j) {
            allInvoices.pushback(invoices[j]);
        }
    }
    for (int i = 0; i < allInvoices.getSize() - 1; ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < allInvoices.getSize(); ++j) {
            if (allInvoices[j]->getInvoiceDate() > allInvoices[maxIndex]->getInvoiceDate()) {
                maxIndex = j; 
            }
        }
        if (maxIndex != i) {
            Invoice* temp = allInvoices[i];
            allInvoices[i] = allInvoices[maxIndex];
            allInvoices[maxIndex] = temp;
        }
    }
    delete customerData;
    return allInvoices;
}
Vector<Invoice*> AppController:: loadAllInvoice(){
    DataController* customerData = new DataController();
    Vector<Customer> customers = customerData->loadAllCustomersData();
    Vector<Invoice*> allInvoices;
    for (int i = 0; i < customers.getSize(); ++i) {
        Vector<Invoice*> invoices = customerData->loadOrdersData(customers[i].getUserId()).getInvoice();
        for (int j = 0; j < invoices.getSize(); ++j) {
            allInvoices.pushback(invoices[j]);
        }
    }
    delete customerData;
    return allInvoices;
}

string AppController::createProductId() {
    DataController* data = new DataController();
    Vector<Product> allProducts = data->loadProductData();
    string lastId = allProducts[allProducts.getSize() - 1].getProductId();

    string id;
    do {
        id = "PRD0" + std::to_string(allProducts.getSize() + 1);
    } while (id == lastId); 

    delete data;
    return id;
}
Vector<Pair<string,int>>  AppController:: sortSoldProducts(){
    DataController data;
    Vector<Pair<string,int>> soldProducts = data.loadSoldProductData();
    for (int i = 1; i < soldProducts.getSize(); ++i) {
        Pair<std::string, int> key = soldProducts[i];
        int j = i - 1;
        while (j >= 0 && soldProducts[j].getSecond() < key.getSecond()) {
            soldProducts[j + 1] = soldProducts[j];
            --j;
        }

        soldProducts[j + 1] = key;
    }
    return soldProducts;
}

Vector<Pair<Customer, double>> AppController::sortCustomerByAmount() {
    DataController data;
    Vector<Customer> customers = data.loadAllCustomersData();
    Vector<Pair<Customer, double>> customerTotalData;

    for (int i = 0; i < customers.getSize(); i++) {
        Vector<Invoice*> invoices = data.loadOrdersData(customers[i].getUserId()).getInvoice();
        double totalPrice = 0.0;
        for (int j = 0; j < invoices.getSize(); ++j) {
            totalPrice += invoices[j]->getTotalAmount();
        }
        for (int j = 0; j < invoices.getSize(); j++) {
            totalPrice += invoices[j]->getTotalAmount();
        }
        customerTotalData.pushback(Pair<Customer, double>(customers[i], totalPrice));
    }

    for (int i = 1; i < customerTotalData.getSize(); i++) {
        Pair<Customer, double> keyPair = customerTotalData[i];
        double keyTotal = keyPair.getSecond();
        int j = i - 1;
        while (j >= 0 && customerTotalData[j].getSecond() < keyTotal) {
            customerTotalData[j + 1] = customerTotalData[j];
            j--;
        }
        customerTotalData[j + 1] = keyPair;
    }

    return customerTotalData;
}