#include "Controller/AppController.h"

AppController::AppController() {
}

AppController::~AppController() {
}

Pair<string, string> AppController::allLogin(const string& email, const string& password) {
    Vector<string> role = {"Customer", "Manager", "Employee"};
    string userId;
    
    if ((userId = login(email, password, role[0])) != "Invalid") {
        return Pair<string, string>(role[0], userId);
    }
    else if ((userId = login(email, password, role[1])) != "Invalid") {
        return Pair<string, string>(role[1], userId);
    }
    else if ((userId = login(email, password, role[2])) != "Invalid") {
        return Pair<string, string>(role[2], userId);
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
    else if (role == "Employee") {
        DataController data;
        Vector<Employee> allEmployees = data.loadAllEmployeesData();
        for (int i = 0; i < allEmployees.getSize(); i++) {
            if (allEmployees[i].getEmail() == email && allEmployees[i].getPassword() == password) {
                return allEmployees[i].getUserId();
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
    else if (role == "Employee") {
        Vector<Employee> allEmployees = data->loadAllEmployeesData();
        id = "USER"+ to_string(allEmployees.getSize() + 1);
        Employee *newEmployee = new Employee(id, name, email, phone, password, address);
        data->addEmployee(*newEmployee); 
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
    
    // Tải tất cả khách hàng
    Vector<Customer> customers = customerData->loadAllCustomersData();
    Vector<Invoice*> allInvoices;
    
    // Lấy hóa đơn của tất cả khách hàng
    for (int i = 0; i < customers.getSize(); ++i) {
        Vector<Invoice*> invoices = customerData->loadOrdersData(customers[i].getUserId()).getInvoice();
        for (int j = 0; j < invoices.getSize(); ++j) {
            allInvoices.pushback(invoices[j]);
        }
    }

    for (int i = 0; i < allInvoices.getSize() - 1; ++i) {
        int maxIndex = i; // Giả sử phần tử i là nhỏ nhất
        for (int j = i + 1; j < allInvoices.getSize(); ++j) {
            // Nếu ngày của hóa đơn ở vị trí j nhỏ hơn ngày của hóa đơn ở vị trí maxIndex
            if (allInvoices[j]->getInvoiceDate() > allInvoices[maxIndex]->getInvoiceDate()) {
                maxIndex = j; // Cập nhật maxIndex
            }
        }
        
        // Hoán đổi phần tử ở vị trí i với phần tử ở vị trí maxIndex
        if (maxIndex != i) {
            Invoice* temp = allInvoices[i];
            allInvoices[i] = allInvoices[maxIndex];
            allInvoices[maxIndex] = temp;
        }
    }

    return allInvoices;
}
