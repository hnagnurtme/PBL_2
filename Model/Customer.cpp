#include "Customer.h"
#include <iostream>
Customer :: Customer(){

}
Customer::Customer(const Customer& other) : User(other) { 
    this->cart = new Cart(*other.cart);  
    this->orderHistory = new Orders(*other.orderHistory);  
    this->favouriteProducts = new Vector<Product*>(*other.favouriteProducts);  
}

Customer ::Customer(const string& userId) {
    cart = new Cart(userId);
    orderHistory = new Orders(userId);
    favouriteProducts = new Vector<Product*>;
    this->setUserId(userId);
}

Customer::Customer(const string& id, const string& name, const string& email, const string& phone, const string& password, const string& address) : User(id,name,email,phone,password,address){
    cart = new Cart(userId);
    orderHistory = new Orders(userId);
    favouriteProducts = new Vector<Product*>;
}
Customer :: ~Customer(){
    delete cart;
    delete orderHistory; 
    delete favouriteProducts;
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

void  Customer:: addToFavourite(Product* product){
    if (favouriteProducts == nullptr) {
        favouriteProducts = new Vector<Product*> ;
        }
        favouriteProducts->pushback(product);
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

