#include "Controller/LoginController.h"

bool LoginController :: authenLogin(const string &email, const string &password){
    if(authenciation.loginAuthentication(email,password)) return true;
    else return false;
}