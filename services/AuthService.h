#pragma once

#include "../storage/header/UserStorage.h"
#include "../storage/header/AdminStorage.h"

class AuthService
{
private:
    UserStorage userStorage;
    AdminStorage adminStorage;

public:
    bool registerUser(
        const char *fullName,
        const char *email,
        const char *password,
        const char *number,
        const char *address);

    int loginUser(
        const char *email,
        const char *password);

    bool loginAdmin(
        const char *username,
        const char *password);
};
