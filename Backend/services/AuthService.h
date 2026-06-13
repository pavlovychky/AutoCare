#pragma once

#include "../storage/UserStorage.h"
#include "../storage/CartStorage.h"

class AuthService
{
private:
    UserStorage *userStorage;
    CartStorage *cartStorage;

public:
    AuthService(UserStorage *userStorage, CartStorage *cartStorage);

    User *registerUser(const char *fullName, const char *email, const char *password,
                       const char *number, const char *address, UserRole role);
    User *login(const char *email, const char *password);
};
