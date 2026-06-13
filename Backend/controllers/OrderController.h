#pragma once

#include "crow.h"
#include "../services/OrderService.h"
#include "../storage/OrderStorage.h"
#include "../storage/ProductStorage.h"
#include "../storage/UserStorage.h"

class OrderController
{
private:
    OrderService& orderService;
    OrderStorage& orderStorage;
    UserStorage& userStorage;
    ProductStorage& productStorage;

    crow::json::wvalue orderToJson(const Order* order);

public:
    OrderController(OrderService& service,
                    OrderStorage& storage,
                    UserStorage& users,
                    ProductStorage& products);

    void registerRoutes(crow::SimpleApp& app);
};
