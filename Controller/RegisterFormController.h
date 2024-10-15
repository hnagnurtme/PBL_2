#pragma once
#include <string>
#include "Object/User.h"
#include "Handle/UserInformationHandle.h"
using namespace std;
class RegisterFormController{
public: 
    UserInformationHandle save;
    void SaveUserInformation(string firstname, string lastname, string address, string phone, string birthday, string gender);
};