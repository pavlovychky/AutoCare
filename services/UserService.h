#pragma once

#include "../domain/User.h"
#include "../storage/header/UserStorage.h"

class UserService
{
private:
    UserStorage storage;

public:
    void registerUser(const char *fullName,
                      const char *email,
                      const char *password,
                      const char *number,
                      const char *address);

    bool login(const char *email, const char *password);
};
