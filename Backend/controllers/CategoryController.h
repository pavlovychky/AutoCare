#pragma once

#include "crow.h"
#include "../storage/CategoryStorage.h"
#include "../storage/UserStorage.h"

class CategoryController
{
private:
    CategoryStorage& categoryStorage;
    UserStorage& userStorage;

    crow::json::wvalue categoryToJson(const Category* category);

public:
    CategoryController(CategoryStorage& storage, UserStorage& users);

    void registerRoutes(crow::SimpleApp& app);
};
