#pragma once
#include "Datastructures/DataStructures.h"
#include <string>
#include <Vector>
#include <iostream>
using namespace std;

class Employee {
protected:
    string EmployeeID;
    string EmployeeName;
    string Address;
    string Phone;
    string Account;
    string Password;

public:
    Employee(const string& employeeID, const string& employeeName, const string& address, const string& phone,
            const string& account, const string& password)
        : EmployeeID(employeeID), EmployeeName(employeeName), Address(address), Phone(phone), Account(account), Password(password) {}

    string getEmployeeID() const { return EmployeeID; }
    string getEmployeeName() const { return EmployeeName; }
    string getAddress() const { return Address; }
    string getPhone() const { return Phone; }
    string getAccount() const { return Account; }
    string getPassword() const { return Password; }

    void setEmployeeName(const string& employeeName) { EmployeeName = employeeName; }
    void setAddress(const string& address) { Address = address; }
    void setPhone(const string& phone) { Phone = phone; }
    void setAccount(const string& account) { Account = account; }
    void setPassword(const string& password) { Password = password; }

    virtual void displayInfo() const {
        cout << "Employee ID: " << EmployeeID << endl;
        cout << "Employee Name: " << EmployeeName << endl;
        cout << "Address: " << Address << endl;
        cout << "Phone: " << Phone << endl;
        cout << "Account: " << Account << endl;
    }
};

class Cashier : public Employee {
private:
    Vector<string> InvoiceIDs;

public:
    Cashier(const string& employeeID, const string& employeeName, const string& address, const string& phone,
            const string& account, const string& password)
        : Employee(employeeID, employeeName, address, phone, account, password) {}

    void addInvoiceID(const string& invoiceID) {
        InvoiceIDs.pushback(invoiceID);
    }

    void displayInfo() const override {
        Employee::displayInfo();
        cout << "Invoice IDs: ";
        for (size_t i = 0; i < InvoiceIDs.getSize(); ++i) {
            cout << InvoiceIDs[i] << " ";
        }
        cout << endl;
    }
};

class Manager : public Employee {
private:
    Vector<string> EmployeeIDs;

public:
    Manager(const string& employeeID, const string& employeeName, const string& address, const string& phone,
            const string& account, const string& password)
        : Employee(employeeID, employeeName, address, phone, account, password) {}

    void addEmployeeID(const string& employeeID) {
        EmployeeIDs.pushback(employeeID);
    }

    void displayInfo() const override {
        Employee::displayInfo();
        cout << "Employee IDs: ";
        for (size_t i = 0; i < EmployeeIDs.getSize(); ++i) {
            cout << EmployeeIDs[i] << " ";
        }
        cout << endl;
    }
};
