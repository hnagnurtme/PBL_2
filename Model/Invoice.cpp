#include "Model/Invoice.h"
#include "Model/Cart.h"
#include "Model/Customer.h"
#include "Controller/DataController.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <random>

void Invoice::setInvoiceID(int count){
    invoiceId = customerId+ "INV_" + to_string(count);
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
    invoiceId = customerId+"INV_" + getInvoiceDate();
}

Invoice::Invoice(const string& invoiceId, const string& customerId, const Vector<Pair<Product*, int>>& products, double totalAmount)
    : invoiceId(invoiceId), customerId(customerId), products(products), totalAmount(totalAmount) {
    setInvoiceDate();
}

string Invoice::displayInvoice() const {
    stringstream ss;
    DataController *dataController = new DataController();
    Customer customer = dataController->findCustomerById(customerId);
    delete dataController;

    ss << "======================== INVOICE ========================\n";

    // In thông tin hóa đơn và khách hàng với dấu ":" thẳng hàng
    auto printLine = [&](const string& label, const string& value) {
        ss << left << setw(20) << label << ": " << setw(35) << value << "\n";  // Tăng độ rộng cột
    };

    printLine("Invoice ID", invoiceId);
    printLine("Customer ID", customerId);
    printLine("Customer Name", customer.getName());
    printLine("Phone", customer.getPhone());
    printLine("Email", customer.getEmail());
    printLine("Address", customer.getAddress());
    printLine("Invoice Date", invoiceDate);
    printLine("Delivery Date", deliveryDate);
    printLine("Payment Method", paymentMethod);

    ss << "--------------------------------------------------------\n";

    // Đảm bảo cột 'Product Name' có độ rộng cố định và thẳng hàng
    ss << left << setw(40) << "Product Name"
       << setw(15) << "Quantity"
       << setw(15) << "Price"
       << setw(15) << "Total" << "\n";
    ss << "--------------------------------------------------------\n";

    for (int i = 0; i < products.getSize(); ++i) {
        double total = products[i].getSecond() * products[i].getFirst()->getPrice();
        ss << left << setw(45) << products[i].getFirst()->getName() // Đảm bảo độ rộng của tên sản phẩm là 40
           << setw(15) << products[i].getSecond()
           << setw(15) << fixed << setprecision(2) << products[i].getFirst()->getPrice() // Định dạng Price với fixed
           << setw(15) << fixed << setprecision(2) << total << "\n"; // Định dạng Total với fixed
    }

    ss << "========================================================\n";
    ss << right << setw(65) << "Total Amount     : $"
       << fixed << setprecision(2) << totalAmount << "\n"; // Định dạng Total Amount với fixed

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