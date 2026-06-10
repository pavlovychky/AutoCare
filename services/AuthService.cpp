#include "../services/AuthService.h"

#include <cstring>

bool AuthService::registerUser(
    const char *fullName,
    const char *email,
    const char *password,
    const char *number,
    const char *address)
{
    User users[100];

    int count = userStorage.getAll(users, 100);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].getEmail(), email) == 0)
        {
            return false;
        }
    }

    User user(
        0,
        fullName,
        email,
        password,
        number,
        address);

    userStorage.add(user);

    return true;
}

int AuthService::loginUser(
    const char *email,
    const char *password)
{
    User users[100];

    int count = userStorage.getAll(users, 100);

    for (int i = 0; i < count; i++)
    {
        if (
            strcmp(users[i].getEmail(), email) == 0 &&
            users[i].checkPassword(password))
        {
            return users[i].getId();
        }
    }

    return -1;
}

bool AuthService::loginAdmin(
    const char *username,
    const char *password)
{
    Admin admins[20];

    int count = adminStorage.getAll(admins, 20);

    for (int i = 0; i < count; i++)
    {
        if (
            strcmp(admins[i].getUsername(), username) == 0 &&
            admins[i].checkPassword(password))
        {
            return true;
        }
    }

    return false;
}
