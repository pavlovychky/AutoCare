#include "../domain/Admin.h"
#include "../include/Utils.h"

Admin::Admin()
{
    username[0] = '\0';
    password = 0;
}

Admin::Admin(const char *username, const char *password)
{
    utils::CopyString(
        this->username,
        username,
        sizeof(this->username));

    this->password = utils::Hash(password);
}

const char *Admin::getUsername() const
{
    return username;
}

unsigned long Admin::getPassword() const
{
    return password;
}

void Admin::setUsername(const char *username)
{
    utils::CopyString(
        this->username,
        username,
        sizeof(this->username));
}

void Admin::setPassword(const char *password)
{
    this->password = utils::Hash(password);
}

bool Admin::checkPassword(const char *password) const
{
    return this->password == utils::Hash(password);
}
