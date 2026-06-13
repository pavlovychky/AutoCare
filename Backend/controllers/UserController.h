#pragma once

#include "crow.h"
#include "../storage/UserStorage.h"

class UserController
{
private:
    UserStorage& userStorage;

    crow::json::wvalue userToJson(const User* user);

public:
    UserController(UserStorage& storage);

    void registerRoutes(crow::SimpleApp& app);
};