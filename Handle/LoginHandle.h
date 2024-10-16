#pragma once
#include <string>
#include "Datastructures/DataStructures.h"
#include "Object/User.h"
class LoginHandle{
private:
    Vector<User> listUsers;
public:
    public:
    bool loginAuthentication(const string &email, const string &password);
    void saveAccount(const string &email, const string &password);
    bool sendRequestRecover(const string &email);
    bool generateOTP(const string& email, const Vector<pair<string, string>>& accounts);
    bool authentiacationRequest(const string &otp);
    bool recoverPassword(const string &otp,const string &newpassword);
};