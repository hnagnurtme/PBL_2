#pragma once
#include "Model/Product.h"
#include "Model/Cart.h"
#include "Model/Invoice.h"
#include "Model/Orders.h"
#include "Model/Customer.h"
#include "Model/Employee.h"
#include "Model/Manager.h"
#include "Datastructures/Vector.h"
#include "Datastructures/Pair.h"
#include "Controller/DataController.h"
#include <vector>
#include <string>
using namespace std; 
class AppController{
    public:
    Pair<string,string> allLogin(const string& email , const string& password);
    string login(const string& email , const string& password,const string& role);
    string signin( const string& name, const string& email, const string& phone, const string& password, const string& address,const string& role);
    Vector<Invoice*> sortInvoiceByDate();
};