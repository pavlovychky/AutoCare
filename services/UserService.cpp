#include "UserService.h"
#include "../include/Utils.h"

void UserService::registerUser(const char *fullName,
                               const char *email,
                               const char *password,
                               const char *number,
                               const char *address)
{
    User user(fullName, email, password, number, address);
    storage.add(user);
}

bool UserService::login(const char *email, const char *password)
{
    User users[100];
    int count = storage.getAll(users, 100);

    unsigned long hash = utils::Hash(password);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].getEmail(), email) == 0 &&
            users[i].checkPassword(password))
        {
            return true;
        }
    }

    return false;
}
