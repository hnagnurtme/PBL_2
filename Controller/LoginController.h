#pragma once
#include <string>
#include "Object/User.h"
#include "Handle/LoginHandle.h"

class LoginController{
public:
    LoginHandle authenciation;
    bool authenLogin(const string &email, const string &password);
};