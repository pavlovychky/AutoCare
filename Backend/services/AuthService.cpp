#include "AuthService.h"

AuthService::AuthService(UserStorage *userStorage, CartStorage *cartStorage)
{
    this->userStorage = userStorage;
    this->cartStorage = cartStorage;
}

User *AuthService::registerUser(const char *fullName, const char *email, const char *password,
                                const char *number, const char *address, UserRole role)
{
    if (fullName == 0 || email == 0 || password == 0 || fullName[0] == '\0' || email[0] == '\0' || password[0] == '\0')
    {
        return 0;
    }

    User *user = userStorage->create(fullName, email, password, number, address, role);
    if (user != 0 && user->isClient())
    {
        cartStorage->create(user->getId());
    }

    return user;
}

User *AuthService::login(const char *email, const char *password)
{
    User *user = userStorage->getByEmail(email);
    if (user != 0 && user->checkPassword(password))
    {
        return user;
    }

    return 0;
}
