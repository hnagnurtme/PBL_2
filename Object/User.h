#pragma once
#include <string>
using namespace std;

class User {
private:
    string firstname;
    string lastname;
    string address;
    string phone;
    string birthday;
    string gender;

public:
    User(string firstname ="", string lastname ="", string address="", string phone="", string birthday="", string gender="");
    
    string getFirstName() const;
    string getLastName() const;
    string getAddress() const;
    string getPhone() const;
    string getBirthday() const;
    string getGender() const;
};
