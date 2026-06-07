#include "../storage/header/UserStorage.h"
#include "../include/IDGenerator.h"

#include <cstdio>

void UserStorage::add(User &user)
{
    int id = IDGenerator::GetNextId("users.id");

    user.setId(id);

    FILE* file = fopen(FILE_NAME, "ab");

    if (file == NULL)
        return;

    fwrite(&user, sizeof(User), 1, file);

    fclose(file);
}

int UserStorage::getAll(User users[], int maxCount)
{
    FILE* file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return 0;

    int count = 0;

    while (
        count < maxCount &&
        fread(&users[count], sizeof(User), 1, file) == 1)
    {
        count++;
    }

    fclose(file);

    return count;
}

bool UserStorage::getById(int id, User &result)
{
    FILE* file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return false;

    User temp;

    while (fread(&temp, sizeof(User), 1, file) == 1)
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

bool UserStorage::update(const User &updatedUser)
{
    FILE* file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
        return false;

    User temp;

    while (fread(&temp, sizeof(User), 1, file) == 1)
    {
        if (temp.getId() == updatedUser.getId())
        {
            fseek(file, -static_cast<long>(sizeof(User)), SEEK_CUR);

            fwrite(&updatedUser, sizeof(User), 1, file);

            fclose(file);

            return true;
        }
    }

    fclose(file);

    return false;
}

bool UserStorage::deleteUser(int id)
{
    FILE* file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return false;

    FILE* tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL)
    {
        fclose(file);
        return false;
    }

    User temp;
    bool deleted = false;

    while (fread(&temp, sizeof(User), 1, file) == 1)
    {
        if (temp.getId() != id)
        {
            fwrite(&temp, sizeof(User), 1, tempFile);
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
