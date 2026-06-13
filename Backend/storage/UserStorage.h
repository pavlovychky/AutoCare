#pragma once

#include "../domain/User.h"

class UserStorage
{
private:
    User users[MAX_USERS];
    int count;
    int nextId;

public:
    UserStorage();

    User *create(const char *fullName, const char *email, const char *password,
                 const char *number, const char *address, UserRole role);
    User *getById(int id);
    User *getByEmail(const char *email);
    bool update(const User &user);
    bool remove(int id);

    int getCount() const;
    bool saveToBinaryFile(const char *fileName) const;
    bool loadFromBinaryFile(const char *fileName);
};
