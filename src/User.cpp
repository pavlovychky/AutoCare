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
    utils::CopyString(this->fullName, fullName, sizeof(this->fullName));
    utils::CopyString(this->email, email, sizeof(this->email));
    utils::CopyString(this->number, number, sizeof(this->number));
    utils::CopyString(this->address, address, sizeof(this->address));
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
    utils::CopyString(this->fullName, name, sizeof(this->fullName));
}

void User::setEmail(const char *email)
{
    utils::CopyString(this->email, email, sizeof(this->email));
}

void User::setPassword(const char *password)
{
    this->password = utils::Hash(password);
}

bool User::checkPassword(const char *password) const
{
    return this->password == utils::Hash(password);
}

void User::setId(int id)
{
    this->id_user = id;
}
