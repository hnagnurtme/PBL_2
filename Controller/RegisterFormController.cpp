#include "Controller/RegisterFormController.h"

void RegisterFormController::SaveUserInformation(string firstname, string lastname, string address, string phone, string birthday, string gender){
    User newUser(firstname,lastname,address,phone,birthday,gender);
    save.SaveUserInformation(newUser);
}

void RegisterFormController:: SaveAccount(const string &email, const string &password){
    save.SaveAccount(email,password);
}