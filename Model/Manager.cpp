#include "Model/Manager.h"
#include "Controller/DataController.h"

Manager ::Manager (){}

Manager :: Manager(const string& id, const string& name, const string& email, const string& phone, const string& password, const string& address):User(id,name,email,phone,password,address){}

void Manager::addNewProduct(Product& product) {
    DataController data;
    Vector<Product> listProducts = data.loadProductData();
    for (int i = 0; i < listProducts.getSize(); ++i) {
        if (listProducts[i].getProductId() == product.getProductId()) {
            listProducts.remove(i);
            break; 
        }
    }
    
    listProducts.pushback(product);
    data.saveProductsData(listProducts);
}

bool Manager ::removeProduct(const string& id){
    DataController data;
    Vector<Product> listProducts = data.loadProductData();
    for(int i = 0; i < listProducts.getSize(); i++){
        if(listProducts[i].getProductId() == id){
            listProducts.remove(i);
            data.saveProductsData(listProducts);
            return true;
        }
    }
    return false;
}