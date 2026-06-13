#include "AuthController.h"
#include <string>

AuthController::AuthController(AuthService& service) : authService(service) {}

crow::json::wvalue AuthController::userToJson(const User* user) {
    crow::json::wvalue j;
    if (user == nullptr) return j;

    j["id"] = user->getId();
    j["fullName"] = user->getFullName(); 
    j["email"] = user->getEmail();
    j["number"] = user->getNumber();
    j["address"] = user->getAddress();
    j["isAdmin"] = user->isAdmin();
    j["isClient"] = user->isClient();
    
    return j;
}

// Змінено назву на registerRoutes відповідно до AuthController.h
void AuthController::registerRoutes(crow::SimpleApp& app) {

    // 1. POST: Реєстрація нового користувача (/api/auth/register)
    CROW_ROUTE(app, "/api/auth/register").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("fullName") || !body.has("email") || !body.has("password")) {
            return crow::response(400, "Missing required fields (fullName, email, password)");
        }

        std::string fullName = body["fullName"].s();
        std::string email = body["email"].s();
        std::string password = body["password"].s();
        
        std::string number = "";
        if (body.has("number")) {
            number = body["number"].s();
        }

        std::string address = "";
        if (body.has("address")) {
            address = body["address"].s();
        }
        
        int roleInt = body.has("role") ? body["role"].i() : ROLE_CLIENT;
        UserRole role = static_cast<UserRole>(roleInt);

        User* registeredUser = authService.registerUser(
            fullName.c_str(), email.c_str(), password.c_str(), 
            number.c_str(), address.c_str(), role
        );

        if (registeredUser == nullptr) {
            return crow::response(400, "Registration failed. Email might already exist or invalid data.");
        }

        return crow::response(201, userToJson(registeredUser));
    });

    // 2. POST: Вхід у систему (/api/auth/login)
    CROW_ROUTE(app, "/api/auth/login").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("email") || !body.has("password")) {
            return crow::response(400, "Email and password are required.");
        }

        std::string email = body["email"].s();
        std::string password = body["password"].s();

        User* user = authService.login(email.c_str(), password.c_str());

        if (user == nullptr) {
            crow::json::wvalue errorMsg;
            errorMsg["error"] = "Invalid email or password";
            return crow::response(401, errorMsg);
        }

        return crow::response(200, userToJson(user));
    });
}
