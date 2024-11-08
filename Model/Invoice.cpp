#include "Model/Invoice.h"
#include "Model/Cart.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <random>

void Invoice::setInvoiceID(int count){
    invoiceId = "INV_" + to_string(count);
}

Invoice::Invoice() : customerId(""), totalAmount(0.0) {
    setInvoiceDate();
    invoiceId = "INV_" + getInvoiceDate();
}

Invoice::Invoice(const Cart& cart) : customerId(cart.getCustomerID()), totalAmount(0.0) {
    Vector<Pair<Product*, int>> productsInCart = cart.getItems(); 

    for (int i = 0; i < productsInCart.getSize(); ++i) {
        Product* product = productsInCart[i].getFirst();
        int quantity = productsInCart[i].getSecond();

        addProductToInvoice(product, quantity); 
        totalAmount += product->getPrice() * quantity;
    }

    setInvoiceDate();
    invoiceId = "INV_" + getInvoiceDate();
}


Invoice::Invoice(const string& invoiceId, const string& customerId, const Vector<Pair<Product*, int>>& products, double totalAmount)
    : invoiceId(invoiceId), customerId(customerId), products(products), totalAmount(totalAmount) {
    setInvoiceDate();
}

string Invoice::displayInvoice() const {
    stringstream ss;
    ss << "======================== INVOICE ========================\n";
    ss << left << setw(20) << "Invoice ID"      << ": " << invoiceId << "\n";
    ss << left << setw(20) << "Customer ID"     << ": " << customerId << "\n";
    ss << left << setw(20) << "Invoice Date"    << ": " << invoiceDate << "\n";
    ss << left << setw(20) << "Delivery Date"   << ": " << deliveryDate << "\n";
    ss << left << setw(20) << "Payment Method"  << ": " << paymentMethod << "\n";
    ss << "\n--------------------------------------------------------------------------------------------\n";
    
    // Tiêu đề bảng sản phẩm
    ss << left << setw(30) << "Product Name" << "| "
       << setw(10) << "Quantity" << "| " << setw(10) << "Price" << "\n";
    ss << "--------------------------------------------------------------------------------------------\n";
    
    // Liệt kê sản phẩm
    for (int i = 0; i < products.getSize(); ++i) {
        ss << left << setw(30) << products[i].getFirst()->getName()
           << "| " << setw(10) << products[i].getSecond()
           << "| " << setw(10) << fixed << setprecision(2) << products[i].getFirst()->getPrice() << "\n";
    }

    // Tổng số tiền
    ss << "======================================================\n";
    ss << right << setw(45) << "Total Amount     : $" << fixed << setprecision(2) << totalAmount << "\n";
    
    return ss.str();
}

Vector<Pair<Product*, int>> Invoice:: getProducts() const{
    return products;
}

string Invoice::getInvoiceId() const {
    return invoiceId;
}

void Invoice::setInvoiceId(const string& id) {
    invoiceId = id;
}

string Invoice::getCustomerId() const {
    return customerId;
}

void Invoice::setCustomerId(const string& id) {
    customerId = id;
}

void Invoice::setInvoiceDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    stringstream ss;
    ss << put_time(localTime, "%Y-%m-%d"); 
    invoiceDate = ss.str();
}

string Invoice::getInvoiceDate() const {
    return invoiceDate;
}

void Invoice::setTotalAmount(double amount) {
    totalAmount = amount;
}

double Invoice::getTotalAmount() const {
    return totalAmount;
}

void Invoice::setDeliveryDate(const string& deliveryDate) {
    this->deliveryDate = deliveryDate;
}

void Invoice::setPaymentMethod(const string& paymentMethod) {
    this->paymentMethod = paymentMethod;
}

void Invoice:: addProductToInvoice(Product* product ,int count){
    products.pushback(Pair<Product*, int>(const_cast<Product*>(product), count));
}

string Invoice:: getPaymentMethod(){
    return paymentMethod;
}

string Invoice::getDeliveryDate(){
    return deliveryDate;
}

void Invoice:: setInvoiceDate(const string& date){
    invoiceDate = date;
}

