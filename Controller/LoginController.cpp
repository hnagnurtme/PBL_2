#include "Controller/LoginController.h"

string LoginController :: emailRecover ="";

bool LoginController::authenLogin(const string &email, const string &password) {
    return authentication.loginAuthentication(email, password);
}

bool LoginController::sendRequestRecover(const string &email) {
    emailRecover = email;  
    return request.sendrequestRecover(email);
}

bool LoginController::authenticationRequest(const string &otp) {
    return authentication.authentiacationRequest(otp, emailRecover);
}

bool LoginController::recoverPassword(const string &newpassword) {
    return authentication.recoverPassword(emailRecover, newpassword);
}
