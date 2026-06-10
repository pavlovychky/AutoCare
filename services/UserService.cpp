#include "../services/UserService.h"

void UserService::createUser(
    const char *fullName,
    const char *email,
    const char *password,
    const char *number,
    const char *address)
{
    User user(
        0,
        fullName,
        email,
        password,
        number,
        address);

    storage.add(user);
}

bool UserService::getUserById(int id, User &user)
{
    return storage.getById(id, user);
}

int UserService::getAllUsers(User users[], int maxCount)
{
    return storage.getAll(users, maxCount);
}

bool UserService::updateUser(const User &user)
{
    return storage.update(user);
}

bool UserService::deleteUser(int id)
{
    return storage.deleteUser(id);
}
