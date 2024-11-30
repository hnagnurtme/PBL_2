#include "Model/User.h"
#include <iostream>
using namespace std;
#include <stdexcept>
User::User(){}

User::User(string id, const string& name, const string& email, const string& phone, const string& password,const string& address)
    : userId(id), name(name), email(email), phone(phone), password(password),address(address) {}

bool User::login(string email, string password) {
        if (this->email == email && this->password == password) 
            return true; 
        else return false; 
}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPhone() const { return phone; }
string User::getPassword() const { return password; }
string User::getAddress() const{ return address;};

void User::setUserId(string id) { userId = id; }
void User::setName(const string& name) { this->name = name; }
void User::setEmail(const string& email) { this->email = email; }
void User::setPhone(const string& phone) { this->phone = phone; }
void User::setPassword(const string& password) { this->password = password; }
void User::setAddress(const string& address) { this->address = address; }