#pragma once

#include "../../domain/Cart.h"

class CartStorage
{
private:
    const char* FILE_NAME = "carts.dat";

public:
    void save(Cart& cart);

    bool getByUserId(int userId, Cart& result);

    bool update(Cart& cart);

    bool deleteByUserId(int userId);
};
