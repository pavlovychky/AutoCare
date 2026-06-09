#include "../include/IDGenerator.h"

#include <cstdio>
#include "../storage/header/CategoryStorage.h"

void CategoryStorage::add(Category &category)
{
    int id = IDGenerator::GetNextId("categories.id");

    category.setId(id);

    FILE *file = fopen(FILE_NAME, "ab");

    if (file == NULL)
        return;

    fwrite(&category, sizeof(Category), 1, file);

    fclose(file);
}

int CategoryStorage::getAll(Category categories[], int maxCount)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return 0;

    int count = 0;

    while (
        count < maxCount &&
        fread(&categories[count], sizeof(Category), 1, file) == 1)
    {
        count++;
    }

    fclose(file);

    return count;
}

bool CategoryStorage::getById(int id, Category &result)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return false;

    Category temp;

    while (fread(&temp, sizeof(Category), 1, file) == 1)
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

bool CategoryStorage::update(const Category &updatedCategory)
{
    FILE *file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
        return false;

    Category temp;

    while (fread(&temp, sizeof(Category), 1, file) == 1)
    {
        if (temp.getId() == updatedCategory.getId())
        {
            fseek(file, -static_cast<long>(sizeof(Category)), SEEK_CUR);

            fwrite(&updatedCategory, sizeof(Category), 1, file);

            fclose(file);

            return true;
        }
    }

    fclose(file);

    return false;
}

bool CategoryStorage::deleteCategory(int id)
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

    Category temp;
    bool deleted = false;

    while (fread(&temp, sizeof(Category), 1, file) == 1)
    {
        if (temp.getId() != id)
        {
            fwrite(&temp, sizeof(Category), 1, tempFile);
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
