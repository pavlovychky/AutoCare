#pragma once

#include "CartService.h"
#include "../storage/OrderStorage.h"

class OrderService
{
private:
    OrderStorage *orderStorage;
    CartStorage *cartStorage;
    ProductStorage *productStorage;
    CartService *cartService;

    bool productsAvailable(const Cart *cart);
    void decreaseProductQuantity(const Cart *cart);

public:
    OrderService(OrderStorage *orderStorage, CartStorage *cartStorage,
                 ProductStorage *productStorage, CartService *cartService);

    Order *createFromCart(const User *user, const char *orderDate,
                          DeliveryMethod deliveryMethod, const char *deliveryAddress);
    bool changeStatus(const User *admin, int orderId, OrderStatus status);
};
