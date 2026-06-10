#include "../storage/header/AdminStorage.h"
#include <cstdio>

bool AdminStorage::save(const Admin &admin)
{
    FILE* file = fopen(FILE_NAME, "wb");

    if (file == NULL)
        return false;

    fwrite(&admin, sizeof(Admin), 1, file);

    fclose(file);

    return true;
}

bool AdminStorage::get(Admin &admin)
{
    FILE* file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return false;

    bool success =
        fread(&admin, sizeof(Admin), 1, file) == 1;

    fclose(file);

    return success;
}

bool AdminStorage::update(const Admin &admin)
{
    return save(admin);
}

int AdminStorage::getAll(Admin admins[], int maxCount)
{
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return 0;

    int count = 0;
    while (count < maxCount && fread(&admins[count], sizeof(Admin), 1, file) == 1)
    {
        count++;
    }

    fclose(file);

    return count;
}
