#pragma once

#include "../domain/User.h"
#include "../storage/header/UserStorage.h"

class UserService
{
private:
    UserStorage storage;

public:
    void createUser(
        const char *fullName,
        const char *email,
        const char *password,
        const char *number,
        const char *address);

    bool getUserById(int id, User &user);

    int getAllUsers(User users[], int maxCount);

    bool updateUser(const User &user);

    bool deleteUser(int id);
};