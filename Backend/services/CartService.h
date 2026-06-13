#pragma once

#include "../storage/CartStorage.h"
#include "../storage/ProductStorage.h"
#include "../domain/User.h"

class CartService
{
private:
    CartStorage *cartStorage;
    ProductStorage *productStorage;

public:
    CartService(CartStorage *cartStorage, ProductStorage *productStorage);

    bool addProduct(const User *user, int productId, int quantity);
    bool removeProduct(const User *user, int productId);
    int calculateTotal(const Cart *cart);
};
