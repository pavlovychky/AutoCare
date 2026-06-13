#include "CategoryController.h"
#include <string>

CategoryController::CategoryController(CategoryStorage& storage, UserStorage& users)
    : categoryStorage(storage), userStorage(users)
{
}

crow::json::wvalue CategoryController::categoryToJson(const Category* category)
{
    crow::json::wvalue j;
    if (category == nullptr)
        return j;

    j["id"] = category->getId();
    j["name"] = category->getName();
    j["isActive"] = category->isActive();

    return j;
}

void CategoryController::registerRoutes(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/api/categories")
    ([this]()
    {
        crow::json::wvalue response;
        int jsonIndex = 0;

        for (int i = 0; i < categoryStorage.getCount(); i++)
        {
            Category* category = categoryStorage.getByIndex(i);
            if (category != nullptr && category->isActive())
            {
                response[jsonIndex] = categoryToJson(category);
                jsonIndex++;
            }
        }

        return crow::response(200, response);
    });

    CROW_ROUTE(app, "/api/categories")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("name") || !body.has("adminId"))
        {
            return crow::response(400, "Missing name or adminId");
        }

        User* admin = userStorage.getById(body["adminId"].i());
        if (!admin || !admin->isAdmin())
        {
            return crow::response(403, "Forbidden");
        }

        std::string categoryName = body["name"].s();
        Category* createdCategory = categoryStorage.create(categoryName.c_str());

        if (createdCategory == nullptr)
        {
            return crow::response(400, "Failed to create category");
        }

        return crow::response(201, categoryToJson(createdCategory));
    });
}
