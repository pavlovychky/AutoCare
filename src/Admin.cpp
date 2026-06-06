#include "../domain/Admin.h"
#include <cstring>

Admin::Admin()
{
    username[0] = '\0';
    password[0] = '\0';
}

Admin::Admin(const char *username, unsigned long password)
{
    strcpy(this->username, sizeof(this->username), username);
    this->password = password;
}
