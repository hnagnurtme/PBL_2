#pragma once
#include <string>
using namespace std;
class User {
protected:
    string userId;
    string name;
    string email;
    string phone;
    string password;
    string address;
public:
    User();
    User(string id, const string& name, const string& email, const string& phone, const string& password, const string& address);
    bool login(const string email, const string password);
    void logout();
    void displayInfo() const;

    string getUserId() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    string getPassword() const;
    string getAddress() const;

    void setUserId(string id);
    void setName(const string& name);
    void setEmail(const string& email);
    void setPhone(const string& phone);
    void setPassword(const string& password);
    void setAddress(const string& address);
};