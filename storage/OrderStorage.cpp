#include "../storage/header/OrderStorage.h"
#include "../include/IDGenerator.h"

#include <cstdio>

void OrderStorage::add(Order &order)
{
    int id = IDGenerator::GetNextId("orders.id");

    order.setId(id);

    FILE *file = fopen(FILE_NAME, "ab");

    if (file == NULL)
        return;

    fwrite(&order, sizeof(Order), 1, file);

    fclose(file);
}

int OrderStorage::getAll(Order orders[], int maxCount)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return 0;

    int count = 0;

    while (
        count < maxCount &&
        fread(&orders[count], sizeof(Order), 1, file) == 1)
    {
        count++;
    }

    fclose(file);

    return count;
}

bool OrderStorage::getById(int id, Order &result)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return false;

    Order temp;

    while (fread(&temp, sizeof(Order), 1, file) == 1)
    {
        if (temp.getId() == id)
        {
            result = temp;

            fclose(file);

            return true;
        }
    }

    fclose(file);

    return false;
}

bool OrderStorage::update(const Order &updatedOrder)
{
    FILE *file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
        return false;

    Order temp;

    while (fread(&temp, sizeof(Order), 1, file) == 1)
    {
        if (temp.getId() == updatedOrder.getId())
        {
            fseek(file, -static_cast<long>(sizeof(Order)), SEEK_CUR);

            fwrite(&updatedOrder, sizeof(Order), 1, file);

            fclose(file);

            return true;
        }
    }

    fclose(file);

    return false;
}

bool OrderStorage::deleteOrder(int id)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return false;

    FILE *tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL)
    {
        fclose(file);
        return false;
    }

    Order temp;
    bool deleted = false;

    while (fread(&temp, sizeof(Order), 1, file) == 1)
    {
        if (temp.getId() != id)
        {
            fwrite(&temp, sizeof(Order), 1, tempFile);
        }
        else
        {
            deleted = true;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    return deleted;
};
