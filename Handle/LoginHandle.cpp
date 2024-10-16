#include <iostream>
#include <fstream>
#include "DataStructures/DataStructures.h"
#include "Handle/LoginHandle.h"
#include <string>
#include <sstream>
#include <random> 
#include <chrono>
#include <map>

bool LoginHandle :: loginAuthentication(const string &email, const string &password) {
    ifstream file("Data/Account.txt");
    string line;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedEmail = line.substr(0, commaPos);
                string storedPassword = line.substr(commaPos + 1);
                if (storedEmail == email && storedPassword == password) {
                    found = true;
                    break;
                }
            }
        }
        file.close();
    } else {
        cerr << "Unable to open the account file." << endl;
        return false;
    }

    return found; 
};

void LoginHandle::saveAccount(const string &email, const string &password) {
    ofstream file("Data/Account.txt", ios::app);
    if (file.is_open()) {
        file << email << "," << password << "\n";
        file.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

bool LoginHandle::generateOTP(const string& email, const Vector<pair<string, string>>& accounts) {
    for (int i = 0; i < accounts.getSize(); ++i) {
        const auto& account = accounts[i];
        if (account.first == email) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(100000, 999999);
            string otp = to_string(distr(gen)); 
            auto creationTime = chrono::steady_clock::now(); 
            ofstream file("Data/OTPRequest.txt", ios::app);
            if (file.is_open()) {
                file << "Email: " << email << "\n";
                file << "OTP: " << otp << "\n";
                file << "Creation Time: " << chrono::duration_cast<chrono::seconds>(creationTime.time_since_epoch()).count() << "\n\n";
                file.close();
            } else {
                cerr << "Không thể mở file OTPRequest.txt để ghi." << endl;
                return false;
            }

            return true; 
        }
    }
    return false; 
}

bool LoginHandle::sendRequestRecover(const string &email) {
    ifstream file("Data/Account.txt");
    string line;
    Vector<pair<string, string>> accounts; 
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string emailInFile = line.substr(0, commaPos);
            string passwordInFile = line.substr(commaPos + 1);
            accounts.pushback(make_pair(emailInFile, passwordInFile));
        }
    }
    file.close(); 
    return generateOTP(email, accounts);
}

bool LoginHandle::authentiacationRequest(const string &otp) {
    ifstream file("Data/OTPRequest.txt");
    string line, fileEmail, fileOTP;
    long long fileCreationTime = 0;

    while (getline(file, line)) {
        if (line.find("OTP:") != string::npos) {
            fileOTP = line.substr(5); 
        }
        if (line.find("Creation Time:") != string::npos) {
            istringstream iss(line.substr(14));
            iss >> fileCreationTime; 
        }
    }
    file.close();
    auto currentTime = chrono::steady_clock::now();
    auto currentEpochTime = chrono::duration_cast<chrono::seconds>(currentTime.time_since_epoch()).count();
    if ((currentEpochTime - fileCreationTime) > 30) {
        cout << "OTP đã hết hạn!" << endl;
        return false;
    }

    if (otp == fileOTP) {
        return true;
    } else {
        cout << "OTP không đúng!" << endl;
        return false; 
    }
}

bool LoginHandle::recoverPassword(const string &otp, const string &newPassword) {
    ifstream otpFile("Data/OTPRequest.txt");
    string line;
    string email;
    bool otpFound = false; 

    while (getline(otpFile, line)) {
        if (line.find("OTP: " + otp) != string::npos) {
            getline(otpFile, line); 
            istringstream iss(line);
            getline(iss, email, ':'); 
            email.erase(0, email.find_first_not_of(" \t")); 
            otpFound = true;
            break; 
        }
    }

    otpFile.close(); 

    if (!otpFound) {
        return false; 
    }

    ifstream userFile("Data/Account.txt");
    string updatedContent;
    bool userFound = false;

    while (getline(userFile, line)) {
        istringstream iss(line);
        string storedEmail, storedPassword;
        getline(iss, storedEmail, ','); 
        getline(iss, storedPassword); 

        if (storedEmail == email) {
            storedPassword = newPassword; 
            userFound = true;
        }
        updatedContent += storedEmail + "," + storedPassword + "\n";
    }

    userFile.close(); 

    ofstream outFile("Data/Account.txt");
    outFile << updatedContent;
    outFile.close();

    return userFound;
}
