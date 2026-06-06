#include "../domain/User.h"
#include "../include/Utils.h"
#include <cstring>

User::User()
{
    id_user = 0;
    password = 0;

    fullName[0] = '\0';
    email[0] = '\0';
    number[0] = '\0';
    address[0] = '\0';
}

User::User(int id_user, const char *fullName, const char *email, const char *password, const char *number, const char *address)
{
    this->id_user = id_user;
    unsigned long p = utils::Hash(password);
    this->password = p;
    strcpy_s(this->fullName, sizeof(this->fullName), fullName);
    strcpy_s(this->email, sizeof(this->email), email);
    strcpy_s(this->number, sizeof(this->number), number);
    strcpy_s(this->address, sizeof(this->address), address);
}

int User::getId() const
{
    return id_user;
}

const char *User::getFullName() const
{
    return fullName;
}

const char *User::getEmail() const
{
    return email;
}

void User::setFullName(const char *name)
{
    strncpy_s(this->fullName, sizeof(this->fullName), name);
}

void User::setEmail(const char *email)
{
    strncpy_s(this->email, sizeof(this->email), email);
}

void User::setPassword(const char *password)
{
    this->password = utils::Hash(password);
}

bool Person::CheckPassword(const char *password) const
{
    return this->password == utils::Hash(password);
}
