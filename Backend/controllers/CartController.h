#pragma once

#include "crow.h"
#include "../services/CartService.h"
#include "../storage/CartStorage.h"
#include "../storage/UserStorage.h"

class CartController
{
private:
    CartService& cartService;
    CartStorage& cartStorage;
    UserStorage& userStorage;

    crow::json::wvalue cartToJson(const Cart* cart);

public:
    CartController(
        CartService& service,
        CartStorage& storage,
        UserStorage& uStorage);

    void registerRoutes(crow::SimpleApp& app);
};