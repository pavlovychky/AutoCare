#include <iostream>
#include "../domain/User.h"

User::User()
{
    id_user = 0;
    fullName[0] = '/0';
    email[0] = '/0';
    password[0] = '/0';
    number[0] = '/0';
    address[0] = '/0';
}

User::User(int id_user, const char *fullName, const char *email, const char *password, const char *number, const char *address)
{
    this->id_user = id_user;
    strcpy(this->fullName, fullName);
    strcpy(this->email, email);
    strcpy(this->password, password);
    strcpy(this->number, number);
    strcpy(this->address, address);
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
    if (name)
    {
        strncpy(this->fullName, name, sizeof(this->fullName) - 1);
        this->fullName[sizeof(this->fullName) - 1] = '\0';
    }
    else
    {
        this->fullName[0] = '\0';
    }
}

void User::setEmail(const char *mail)
{
    if (mail)
    {
        strncpy(this->email, mail, sizeof(this->email) - 1);
        this->email[sizeof(this->email) - 1] = '\0';
    }
    else
    {
        this->email[0] = '\0';
    }
}
