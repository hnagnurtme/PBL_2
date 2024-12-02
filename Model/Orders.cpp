#include "Model/Orders.h"
#include <iomanip>
#include <sstream>
Orders::Orders() : customerID("") {}

Orders::Orders(const string& customerId) : customerID(customerId) {}

void Orders::addInvoice(Invoice* invoice) {
    invoices.pushback(invoice);

}

string Orders::getCustomerID() const {
    return customerID;
}

void Orders::setCustomerID(const string& id) {
    customerID = id;
}

Vector<Invoice*> Orders::  getInvoice() const{
    return invoices;
}

Orders ::Orders(const Orders& other){
    customerID = other.customerID;
    invoices = other.invoices;
}