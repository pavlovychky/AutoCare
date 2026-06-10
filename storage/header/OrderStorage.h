#pragma once

#include "../../domain/Order.h"

class OrderStorage
{
private:
    const char *FILE_NAME = "orders.dat";

public:
    void add(Order &order);

    int getAll(Order orders[], int maxCount);

    bool getById(int id, Order &result);

    bool update(Order &updatedOrder);

    bool deleteOrder(int id);
};