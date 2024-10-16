#include "Controller/LoginController.h"

bool LoginController :: authenLogin(const string &email, const string &password){
    if(authenciation.loginAuthentication(email,password)) return true;
    else return false;
}

bool LoginController :: sendRequestRecover(const string &email){
    if(request.sendrequestRecover(email)) return true;
    else return false;
}

bool LoginController ::authentiacationRequest(const string &otp){
    if( authenciation.authentiacationRequest(otp)) return true;
    else return false;
}

bool LoginController :: recoverPassword(const string &otp,const string &newpassword){
    return true;
}
