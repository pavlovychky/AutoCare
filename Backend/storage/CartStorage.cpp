#include "CartStorage.h"
#include <fstream>

CartStorage::CartStorage()
{
    count = 0;
    nextId = 1;
}

Cart *CartStorage::create(int userId)
{
    if (count >= MAX_USERS || getByUserId(userId) != 0)
    {
        return 0;
    }

    carts[count] = Cart(nextId, userId);
    count++;
    nextId++;
    return &carts[count - 1];
}

Cart *CartStorage::getById(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (carts[i].isActive() && carts[i].getId() == id)
        {
            return &carts[i];
        }
    }

    return 0;
}

Cart *CartStorage::getByUserId(int userId)
{
    for (int i = 0; i < count; i++)
    {
        if (carts[i].isActive() && carts[i].getUserId() == userId)
        {
            return &carts[i];
        }
    }

    return 0;
}

bool CartStorage::update(const Cart &cart)
{
    Cart *existing = getById(cart.getId());
    if (existing == 0)
    {
        return false;
    }

    *existing = cart;
    return true;
}

bool CartStorage::remove(int id)
{
    Cart *cart = getById(id);
    if (cart == 0)
    {
        return false;
    }

    cart->setActive(false);
    return true;
}

int CartStorage::getCount() const
{
    return count;
}

bool CartStorage::saveToBinaryFile(const char *fileName) const
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.write((const char *)&count, sizeof(count));
    file.write((const char *)&nextId, sizeof(nextId));
    file.write((const char *)carts, sizeof(carts));
    return file.good();
}

bool CartStorage::loadFromBinaryFile(const char *fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.read((char *)&count, sizeof(count));
    file.read((char *)&nextId, sizeof(nextId));
    file.read((char *)carts, sizeof(carts));
    return file.good();
}
