#include "OrderStorage.h"
#include <fstream>

OrderStorage::OrderStorage()
{
    count = 0;
    nextId = 1;
}

Order *OrderStorage::create(int userId, const Cart &cart, int totalPrice,
                            const char *orderDate, DeliveryMethod deliveryMethod,
                            const char *deliveryAddress)
{
    if (count >= MAX_ORDERS || cart.getItemCount() > MAX_ORDER_ITEMS)
    {
        return 0;
    }

    orders[count] = Order(nextId, userId, cart, totalPrice, orderDate, deliveryMethod, deliveryAddress);
    count++;
    nextId++;
    return &orders[count - 1];
}

Order *OrderStorage::getById(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (orders[i].isActive() && orders[i].getId() == id)
        {
            return &orders[i];
        }
    }

    return 0;
}

Order *OrderStorage::getByIndex(int index)
{
    if (index < 0 || index >= count)
    {
        return 0;
    }

    return &orders[index];
}

int OrderStorage::getByUserId(int userId, Order *result[], int maxResult)
{
    int resultCount = 0;
    for (int i = 0; i < count && resultCount < maxResult; i++)
    {
        if (orders[i].isActive() && orders[i].getUserId() == userId)
        {
            result[resultCount] = &orders[i];
            resultCount++;
        }
    }

    return resultCount;
}

bool OrderStorage::update(const Order &order)
{
    Order *existing = getById(order.getId());
    if (existing == 0)
    {
        return false;
    }

    *existing = order;
    return true;
}

bool OrderStorage::remove(int id)
{
    Order *order = getById(id);
    if (order == 0)
    {
        return false;
    }

    order->setActive(false);
    return true;
}

int OrderStorage::getCount() const
{
    return count;
}

bool OrderStorage::saveToBinaryFile(const char *fileName) const
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.write((const char *)&count, sizeof(count));
    file.write((const char *)&nextId, sizeof(nextId));
    file.write((const char *)orders, sizeof(orders));
    return file.good();
}

bool OrderStorage::loadFromBinaryFile(const char *fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.read((char *)&count, sizeof(count));
    file.read((char *)&nextId, sizeof(nextId));
    file.read((char *)orders, sizeof(orders));
    return file.good();
}
