#pragma once
#include <string>
#include "Object/User.h"
#include "Handle/LoginHandle.h"

class LoginController{
public:
    LoginController();
    LoginHandle authenciation;
    LoginHandle request;
    bool authenLogin(const string &email, const string &password);
    bool sendRequestRecover(const string &email);
    bool authentiacationRequest(const string &otp);
    bool recoverPassword(const string &otp,const string &newpassword);
};