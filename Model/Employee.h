#pragma once
#include "User.h"
#include "Model/User.h"
#include "Model/Product.h"
#include "Model/Orders.h"
#include "Datastructures/Vector.h"
#include <string>
using namespace std;
class Employee : public User {
public:
    Employee();
    Employee(const string& id, const string& name, const string& email, const string& phone, const string& password, const string& address);
};
