#pragma once
#include "User.h"
#include "Model/User.h"
#include "Model/Product.h"
#include "Model/Orders.h"
#include "Datastructures/Vector.h"
#include <string>
using namespace std;
class Manager : public User {
public:
    Manager();
    Manager(const string& id, const string& name, const string& email, const string& phone, const string& password, const string& address);
    void addNewProduct(Product& product);
    bool removeProduct(const string& id);
    void updateProduct(Product& product);
};