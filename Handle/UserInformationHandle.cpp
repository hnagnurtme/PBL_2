#include "Handle/UserInformationHandle.h"
#include <fstream> 
#include <iostream>
using namespace std;

void UserInformationHandle::SaveUserInformation(const User &user) {
    
    ofstream outFile("Data/UserInformation.txt", ios::app); 
    
    if (outFile.is_open()) {
        outFile << user.getFirstName() << ","
                << user.getLastName() << ","
                << user.getAddress() << ","
                << user.getPhone() << ","
                << user.getBirthday() << ","
                << user.getGender() << endl;
        outFile.close(); 
    } else {
        cerr << "Error opening file for writing." << endl; 
    }
    listUsers.pushback(user);
    
}

void UserInformationHandle::SaveAccount(const string &email, const string &password) {
    ofstream file("Data/Account.txt", ios::app);
    if (file.is_open()) {
        file << email << "," << password << "\n";
        file.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}