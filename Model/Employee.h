#pragma once
#include "Model/User.h"
#include "Model/Orders.h"
#include <string>
using namespace std;
class Employee : public User {
private:
    string position;

public:
    void createInvoice(const Orders& order);
};
