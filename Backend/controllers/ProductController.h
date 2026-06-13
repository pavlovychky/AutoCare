#pragma once

#include "crow.h"
#include "../services/ProductService.h"
#include "../storage/ProductStorage.h"
#include "../storage/UserStorage.h"

class ProductController
{
private:
    ProductService& productService;
    ProductStorage& productStorage;
    UserStorage& userStorage;

    crow::json::wvalue productToJson(const Product* product);

public:
    ProductController(ProductService& service,
                      ProductStorage& storage,
                      UserStorage& users);

    void registerRoutes(crow::SimpleApp& app);
};
