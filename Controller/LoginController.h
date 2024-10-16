#pragma once
#include <string>
#include "Object/User.h"
#include "Handle/LoginHandle.h"
using namespace std;

class LoginController{
public:
    static string emailRecover;
    LoginHandle authentication;
    LoginHandle request;
    bool authenLogin(const string &email, const string &password);
    bool sendRequestRecover(const string &email);
    bool authenticationRequest(const string &otp);
    bool recoverPassword(const string &newpassword);
};