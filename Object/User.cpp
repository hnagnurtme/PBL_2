#include "Object/User.h"

User::User(string firstname, string lastname, string address, string phone, string birthday, string gender) {
    this->firstname = firstname;
    this->lastname = lastname;
    this->address = address;
    this->phone = phone;
    this->birthday = birthday;
    this->gender = gender;
}


string User::getFirstName() const {
    return firstname;
}

string User::getLastName() const {
    return lastname;
}

string User::getAddress() const {
    return address;
}

string User::getPhone() const {
    return phone;
}

string User::getBirthday() const {
    return birthday;
}

string User::getGender() const {
    return gender;
}
