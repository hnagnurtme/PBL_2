#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>
#include "DataStructures/DataStructures.h"
#include "Handle/LoginHandle.h"

using namespace std;

bool LoginHandle::loginAuthentication(const string &email, const string &password) {
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
        return false;
    }

    return found;
}

void LoginHandle::saveAccount(const string &email, const string &password) {
    ofstream file("Data/Account.txt", ios::app);
    if (file.is_open()) {
        file << email << "," << password << "\n";
        file.close();
    }
}

string LoginHandle::generateOTP(const string &email) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);

    string otp;
    for (int i = 0; i < 6; ++i) {
        otp += to_string(dis(gen));
    }

    ofstream file("Data/OTPRequest.txt", ios::app);
    if (file.is_open()) {
        file << "Email: " << email << "\n";
        file << "OTP: " << otp << "\n";
        file.close();
    }

    return otp;
}

bool LoginHandle::sendrequestRecover(const string &email) {
    ifstream inFile("Data/Account.txt");
    if (!inFile.is_open()) {
        return false;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string fileEmail, password;

        if (getline(ss, fileEmail, ',') && getline(ss, password)) {
            if (fileEmail == email) {
                string otp = generateOTP(email);
                listOTP.pushback({fileEmail, otp});
                found = true;
                break;
            }
        }
    }

    inFile.close();
    return found;
}

bool LoginHandle::authentiacationRequest(const string &otp) {
    ifstream file("Data/OTPRequest.txt");
    string line, fileOTP;
    while (getline(file, line)) {
        if (line.find("OTP:") != string::npos) {
            fileOTP = line.substr(5);
        }
    }
    file.close();
    return (otp == fileOTP);
}

bool LoginHandle::recoverPassword(const string &otp, const string &newPassword) {
    // Đọc file OTPRequest.txt
    ifstream otpFile("Data/OTPRequest.txt");
    string line;
    string email;
    bool otpFound = false;

    // Tìm kiếm OTP trong file
    while (getline(otpFile, line)) {
        if (line.find("OTP: " + otp) != string::npos) {
            getline(otpFile, line);
            istringstream iss(line);
            getline(iss, email, ':');
            email.erase(0, email.find_first_not_of(" \t")); // Xóa khoảng trắng ở đầu
            email.erase(email.find_last_not_of(" \t") + 1); // Xóa khoảng trắng ở cuối
            otpFound = true;
            break;
        }
    }

    otpFile.close();

    if (!otpFound) {
        return false; // Không tìm thấy OTP
    }

    // Đọc file Account.txt và cập nhật mật khẩu
    ifstream userFile("Data/Account.txt");
    ofstream tempFile("Data/TempAccount.txt");
    bool userFound = false;

    while (getline(userFile, line)) {
        istringstream iss(line);
        string storedEmail, storedPassword;
        getline(iss, storedEmail, ',');
        getline(iss, storedPassword);

        // Cắt bỏ khoảng trắng cho email đã lưu
        storedEmail.erase(0, storedEmail.find_first_not_of(" \t")); // Xóa khoảng trắng ở đầu
        storedEmail.erase(storedEmail.find_last_not_of(" \t") + 1); // Xóa khoảng trắng ở cuối

        // So sánh email đã lưu với email tìm được từ OTP
        if (storedEmail == email) {
            storedPassword = newPassword; // Cập nhật mật khẩu mới
            userFound = true;
        }
        tempFile << storedEmail + "," + storedPassword + "\n"; // Ghi vào file tạm
    }

    userFile.close();
    tempFile.close();

    // Xóa file cũ và đổi tên file tạm
    remove("Data/Account.txt");
    rename("Data/TempAccount.txt", "Data/Account.txt");

    return userFound; // Trả về true nếu đã tìm thấy và cập nhật thành công
}