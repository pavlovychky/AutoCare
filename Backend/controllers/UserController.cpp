#include "UserController.h"

UserController::UserController(UserStorage& storage)
    : userStorage(storage)
{
}

crow::json::wvalue UserController::userToJson(
    const User* user)
{
    crow::json::wvalue json;

    if (!user)
        return json;

    json["id"] = user->getId();
    json["fullName"] = user->getFullName();
    json["email"] = user->getEmail();
    json["number"] = user->getNumber();
    json["address"] = user->getAddress();
    json["role"] = user->getRole();
    json["active"] = user->isActive();

    return json;
}

void UserController::registerRoutes(
    crow::SimpleApp& app)
{
    // GET /users/<id>
    CROW_ROUTE(app, "/users/<int>")
    ([this](int id)
    {
        User* user =
            userStorage.getById(id);

        if (!user)
        {
            return crow::response(
                404,
                "User not found");
        }

        return crow::response(
            userToJson(user));
    });

    // GET /users/email/<email>
    CROW_ROUTE(app,
               "/users/email/<string>")
    ([this](const std::string& email)
    {
        User* user =
            userStorage.getByEmail(
                email.c_str());

        if (!user)
        {
            return crow::response(
                404,
                "User not found");
        }

        return crow::response(
            userToJson(user));
    });

    // POST /login
    CROW_ROUTE(app, "/login")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body =
            crow::json::load(req.body);

        if (!body)
        {
            return crow::response(
                400,
                "Invalid JSON");
        }

        std::string email =
            body["email"].s();

        std::string password =
            body["password"].s();

        User* user =
            userStorage.getByEmail(
                email.c_str());

        if (!user)
        {
            return crow::response(
                401,
                "Invalid credentials");
        }

        if (!user->checkPassword(
                password.c_str()))
        {
            return crow::response(
                401,
                "Invalid credentials");
        }

        return crow::response(
            userToJson(user));
    });
}