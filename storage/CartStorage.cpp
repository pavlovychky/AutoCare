#include "../storage/header/CartStorage.h"

#include <cstdio>

void CartStorage::save(Cart& cart)
{
    FILE* file = fopen(FILE_NAME, "ab");

    if (!file)
        return;

    fwrite(&cart, sizeof(Cart), 1, file);

    fclose(file);
}

bool CartStorage::getByUserId(int userId, Cart& result)
{
    FILE* file = fopen(FILE_NAME, "rb");

    if (!file)
        return false;

    Cart temp;

    while (fread(&temp, sizeof(Cart), 1, file) == 1)
    {
        if (temp.getUserId() == userId)
        {
            result = temp;
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}
bool CartStorage::update(Cart& cart)
{
    FILE* file = fopen(FILE_NAME, "rb+");

    if (!file)
        return false;

    Cart temp;

    while (fread(&temp, sizeof(Cart), 1, file) == 1)
    {
        if (temp.getUserId() == cart.getUserId())
        {
            fseek(file, -static_cast<long>(sizeof(Cart)), SEEK_CUR);
            fwrite(&cart, sizeof(Cart), 1, file);

            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool CartStorage::deleteByUserId(int userId)
{
    FILE* file = fopen(FILE_NAME, "rb");

    if (!file)
        return false;

    FILE* tempFile = fopen("temp.dat", "wb");

    if (!tempFile)
    {
        fclose(file);
        return false;
    }

    Cart temp;
    bool deleted = false;

    while (fread(&temp, sizeof(Cart), 1, file) == 1)
    {
        if (temp.getUserId() != userId)
        {
            fwrite(&temp, sizeof(Cart), 1, tempFile);
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
}
