#pragma once

#include "../domain/Order.h"

class OrderStorage
{
private:
    Order orders[MAX_ORDERS];
    int count;
    int nextId;

public:
    OrderStorage();

    Order *create(int userId, const Cart &cart, int totalPrice,
                  const char *orderDate, DeliveryMethod deliveryMethod,
                  const char *deliveryAddress);
    Order *getById(int id);
    Order *getByIndex(int index);
    int getByUserId(int userId, Order *result[], int maxResult);
    bool update(const Order &order);
    bool remove(int id);

    int getCount() const;
    bool saveToBinaryFile(const char *fileName) const;
    bool loadFromBinaryFile(const char *fileName);
};
