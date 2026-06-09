#pragma once

#include "../../domain/User.h"

class UserStorage
{
private:
    const char *FILE_NAME = "users.dat";

public:
    void add(User &user);

    int getAll(User users[], int maxCount);

    bool getById(int id, User &result);

    bool update(const User &updatedUser);

    bool deleteUser(int id);
};
