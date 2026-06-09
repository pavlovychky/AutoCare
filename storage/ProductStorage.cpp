#include "../storage/header/ProductStorage.h"
#include "../include/IDGenerator.h"

#include <cstdio>

void ProductStorage::add(Product &product)
{
    int id = IDGenerator::GetNextId("products.id");

    product.setId(id);

    FILE *file = fopen(FILE_NAME, "ab");

    if (file == NULL)
        return;

    fwrite(&product, sizeof(Product), 1, file);

    fclose(file);
}

int ProductStorage::getAll(Product products[], int maxCount)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return 0;

    int count = 0;

    while (
        count < maxCount &&
        fread(&products[count], sizeof(Product), 1, file) == 1)
    {
        count++;
    }

    fclose(file);

    return count;
}

bool ProductStorage::getById(int id, Product &result)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return false;

    Product temp;

    while (fread(&temp, sizeof(Product), 1, file) == 1)
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

bool ProductStorage::update(const Product &updatedProduct)
{
    FILE *file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
        return false;

    Product temp;

    while (fread(&temp, sizeof(Product), 1, file) == 1)
    {
        if (temp.getId() == updatedProduct.getId())
        {
            fseek(file, -static_cast<long>(sizeof(Product)), SEEK_CUR);

            fwrite(&updatedProduct, sizeof(Product), 1, file);

            fclose(file);

            return true;
        }
    }

    fclose(file);

    return false;
}

bool ProductStorage::deleteProduct(int id)
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

    Product temp;
    bool deleted = false;

    while (fread(&temp, sizeof(Product), 1, file) == 1)
    {
        if (temp.getId() != id)
        {
            fwrite(&temp, sizeof(Product), 1, tempFile);
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
