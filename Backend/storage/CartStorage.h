#pragma once

#include "../domain/Cart.h"

class CartStorage
{
private:
    Cart carts[MAX_USERS];
    int count;
    int nextId;

public:
    CartStorage();

    Cart *create(int userId);
    Cart *getById(int id);
    Cart *getByUserId(int userId);
    bool update(const Cart &cart);
    bool remove(int id);

    int getCount() const;
    bool saveToBinaryFile(const char *fileName) const;
    bool loadFromBinaryFile(const char *fileName);
};
