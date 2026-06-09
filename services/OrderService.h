#pragma once

#include "../domain/Order.h"
#include "../storage/header/OrderStorage.h"
#include "../storage/header/CartStorage.h"

class OrderService
{
private:
    OrderStorage orderStorage;
    CartStorage cartStorage;

public:
    void createOrderFromCart(int userId);
};
