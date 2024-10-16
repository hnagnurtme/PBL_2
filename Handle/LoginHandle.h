#pragma once
#include <random>
#include <string>
#include <utility>
#include "Datastructures/DataStructures.h"
#include "Object/User.h"
using namespace std;
class LoginHandle{
private:
    Vector<User> listUsers;
    Vector<pair<string, string>> listOTP;
public:
    public:
    bool loginAuthentication(const string &email, const string &password);
    void saveAccount(const string &email, const string &password);
    bool sendrequestRecover(const string &email);
    string generateOTP(const string &email);
    bool authentiacationRequest(const string &otp);
    bool recoverPassword(const string &otp,const string &newpassword);
};