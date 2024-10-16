#pragma once
#include <string>
#include "Datastructures/DataStructures.h"
#include "Object/User.h"
class UserInformationHandle{
private:
    Vector<User> listUsers;
public:
    void SaveUserInformation(const User &user);
};