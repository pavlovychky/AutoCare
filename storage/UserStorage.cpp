#include "../domain/User.h"
#include "UserStorage.h"
#include <cstdio>

#define FILE_NAME "users.dat"

void UserStorage::addUser(const User& user) {
    FILE* file = fopen(FILE_NAME, "ab");
    if (file == NULL) return;

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
}

int UserStorage::getAllUsers(User users[], int maxCount) {
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) return 0;

    int count = 0;

    while (fread(&users[count], sizeof(User), 1, file) == 1) {
        count++;
        if (count >= maxCount) break;
    }

    fclose(file);
    return count;
}

bool UserStorage::findUserById(int id_user, User& result) {
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) return false;

    User temp;

    while (fread(&temp, sizeof(User), 1, file) == 1) {
        if (temp.id_user == id_user) {
            result = temp;
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool UserStorage::updateUser(const User& updatedUser) {
    FILE* file = fopen(FILE_NAME, "rb+");
    if (file == NULL) return false;

    User temp;

    while (fread(&temp, sizeof(User), 1, file) == 1) {
        if (temp.id == updatedUser.id) {
            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&updatedUser, sizeof(User), 1, file);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool UserStorage::deleteUser(int id_user) {
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) return false;

    FILE* tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        fclose(file);
        return false;
    }

    User temp;
    bool deleted = false;

    while (fread(&temp, sizeof(User), 1, file) == 1) {
        if (temp.id != id
        ) {
            fwrite(&temp, sizeof(User), 1, tempFile);
        } else {
            deleted = true;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    return deleted;
}