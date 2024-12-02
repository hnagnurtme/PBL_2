#include "Model/Customer.h"
#include <iostream>
Customer :: Customer(){
}
Customer::Customer(const Customer& other) : User(other) { 
    this->cart = new Cart(*other.cart);  
    this->orderHistory = new Orders(*other.orderHistory);  
}

Customer ::Customer(const string& userId) {
    cart = new Cart(userId);
    orderHistory = new Orders(userId);
    this->setUserId(userId);
}

Customer::Customer(const string& id, const string& name, const string& email, const string& phone, const string& password, const string& address) : User(id,name,email,phone,password,address){
    cart = new Cart(userId);
    orderHistory = new Orders(userId);
}
Customer :: ~Customer(){
    delete cart;
    delete orderHistory; 
}
void Customer::addToCart(Product* product, int quantity) {
    cart->addItem(product, quantity);
}

void Customer::payment(const string& deliveryDate,const string& paymentMethod) {
    Invoice* newInvoice = new Invoice(*cart);
    newInvoice->setDeliveryDate(deliveryDate);
    newInvoice->setCustomerId(userId);
    newInvoice->setPaymentMethod(paymentMethod);
    int count = this->orderHistory->getInvoice().getSize();
    newInvoice->setInvoiceID(count);
    orderHistory->addInvoice(newInvoice);
    cart->clearCart();
    DataController *datacontroller = new DataController();
    datacontroller->saveInvoiceData(*newInvoice);
    datacontroller->saveOrdersData(*orderHistory);
    datacontroller->removeProduct(*newInvoice);
    datacontroller->addToSoldProductData(*newInvoice);
    delete datacontroller;
}

void Customer:: reduceItem(const string& productId, int quantity){
    cart->reduceItem(productId,quantity);
}
void Customer::removeItem(string productId){
    cart->removeItem(productId);
}

Cart* Customer::getCart() const {
    return cart;
}

Orders& Customer::getOrderHistory()  {
    return *orderHistory;
}


void Customer::updateOrderHistory(const Orders& newOrderHistory) {
    if (orderHistory != nullptr) {
        delete orderHistory; 
    }

    orderHistory = new Orders(newOrderHistory);
}

Customer& Customer::operator=(const Customer& other) {
    if (this == &other) {
        return *this;
    }
    User::operator=(other);
    delete cart;
    delete orderHistory;

    if (other.cart) {
        cart = new Cart(*other.cart);
    } else {
        cart = nullptr;
    }

    if (other.orderHistory) {
        orderHistory = new Orders(*other.orderHistory);
    } else {
        orderHistory = nullptr;
    }
    return *this;
}