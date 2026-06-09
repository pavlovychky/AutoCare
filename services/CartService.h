#pragma once

#include "../domain/Cart.h"
#include "../storage/header/CartStorage.h"

class CartService
{
private:
    CartStorage storage;

public:
    void addToCart(int userId, const Product& product);

    void removeFromCart(int userId, int productId);

    double getTotal(int userId);

    void clear(int userId);
};
