#include "../domain/Admin.h"
#include "../include/Utils.h"
#include <cstring>

Admin::Admin()
{
    username[0] = '\0';
    password[0] = '\0';
}

Admin::Admin(const char *username, const char *password)
{
    strcpy(this->username, sizeof(this->username), username);
    this->password = utils::Hash(password);
}

const char *Admin::getUsername() const
{
    return username;
}

const char *Admin::getPassword() const
{
    return password;
}

void Admin::setUsername(const char *username)
{
    strcpy(this->username, sizeof(this->username), username);
}

void Admin::setPassword(const char *password)
{
    this->password = utils::Hash(password);
}
