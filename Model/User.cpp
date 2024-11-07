#include "Model/User.h"
#include <iostream>
using namespace std;
#include <stdexcept>
User::User(){
    
}
User::User(string id, const string& name, const string& email, const string& phone, const string& password,const string& address)
    : userId(id), name(name), email(email), phone(phone), password(password),address(address) {}

bool User::login(string email, string password) {
        if (this->email == email && this->password == password) 
            return true; 
        else return false; 
}


void User::logout() {
    char choice;
    cout << "Ban co muon dang xuat khong? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
    cout << "User " << name << " has logged out." << endl;
    }
}

void User::displayInfo() const {
    cout << "User ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
}

void User::sendRecoveryCode() {
    recoveryCode = to_string(rand() % 900000 + 100000); 
    cout << "A recovery code has been sent to " << email << ": " << recoveryCode << endl;
}

void User::recoverPassword() {
    cout << "Recovering password for user: " << name << endl;
    // Logic to recover password, e.g., sending a recovery email
    cout << "Please enter your registered phone number or email to receive a recovery code." << endl;

    string input;
    cout << "Enter phone or email: ";
    cin >> input;

    if (input == phone || input == email) {
            cout << "Recovery code has been sent to " << (input == phone ? "your phone." : "your email.") << endl;
            cout << "Please enter the recovery code to reset your password." << endl;

        sendRecoveryCode(); 
        string enteredCode;
        cout << "Enter the recovery code: ";
        cin >> enteredCode;

    if (enteredCode == recoveryCode) { 
            cout << "Recovery successful. Please enter your new password: ";
            string newPassword;
            cin >> newPassword;
            password = newPassword;
            cout << "Your password has been reset successfully." << endl;
        } else {
            cout << "Invalid recovery code. Please try again." << endl;
        }
    } else {
            cout << "Invalid contact information. Cannot proceed with password recovery." << endl;
    } 

}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPhone() const { return phone; }
string User::getPassword() const { return password; }

void User::setUserId(string id) { userId = id; }
void User::setName(const string& name) { this->name = name; }
void User::setEmail(const string& email) { this->email = email; }
void User::setPhone(const string& phone) { this->phone = phone; }
void User::setPassword(const string& password) { this->password = password; }