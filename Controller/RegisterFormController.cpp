#include "Controller/RegisterFormController.h"

void RegisterFormController::SaveUserInformation(string firstname, string lastname, string address, string phone, string birthday, string gender){
    User newUser(firstname,lastname,address,phone,birthday,gender);
    save.SaveUserInformation(newUser);
}