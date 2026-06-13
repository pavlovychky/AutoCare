#pragma once

#include "crow.h"
#include "../services/AuthService.h"
#include "../domain/User.h"

class AuthController
{
private:
    AuthService &authService;

    crow::json::wvalue userToJson(
        const User *user);

public:
    AuthController(
        AuthService &service);

    void registerRoutes(
        crow::SimpleApp &app);
};