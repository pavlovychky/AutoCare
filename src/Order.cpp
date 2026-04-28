#include <iostream>
#include "../domain/Order.h"
#include "Order.h"

Order::Order()
{
    id_order = 0;
    userId = 0;
    orderDate[0] = '\0';
    delivery[0] = '\0';
    status[0] = '\0';
    total = 0.0;
    productCount = 0;
}

Order::Order(int id_order, int userId, const char *orderDate, const char *deliveryAddress, const char *status, double totalAmount)
{
    this->id_order = id_order;
    this->userId = userId;
    strcpy(this->orderDate, orderDate);
    strcpy(this->delivery, delivery);
    strcpy(this->status, status);
    this->total = total;
    this->productCount = 0;
}
}

int Order::getId() const
{
    return id_order;
}

double Order::getTotal() const
{
    return total;
}

void Order::addProduct(const Product &product)
{
    if (productCount < 50)
    {
        products[productCount] = product;
        productCount++;
    }
}
