#include "UserStorage.h"
#include <cstring>
#include <fstream>

UserStorage::UserStorage()
{
    count = 0;
    nextId = 1;
}

User *UserStorage::create(const char *fullName, const char *email, const char *password,
                          const char *number, const char *address, UserRole role)
{
    if (count >= MAX_USERS || getByEmail(email) != 0)
    {
        return 0;
    }

    users[count] = User(nextId, fullName, email, password, number, address, role);
    count++;
    nextId++;
    return &users[count - 1];
}

User *UserStorage::getById(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (users[i].isActive() && users[i].getId() == id)
        {
            return &users[i];
        }
    }

    return 0;
}

User *UserStorage::getByEmail(const char *email)
{
    for (int i = 0; i < count; i++)
    {
        if (users[i].isActive() && std::strcmp(users[i].getEmail(), email) == 0)
        {
            return &users[i];
        }
    }

    return 0;
}

bool UserStorage::update(const User &user)
{
    User *existing = getById(user.getId());
    if (existing == 0)
    {
        return false;
    }

    *existing = user;
    return true;
}

bool UserStorage::remove(int id)
{
    User *user = getById(id);
    if (user == 0)
    {
        return false;
    }

    user->setActive(false);
    return true;
}

int UserStorage::getCount() const
{
    return count;
}

bool UserStorage::saveToBinaryFile(const char *fileName) const
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.write((const char *)&count, sizeof(count));
    file.write((const char *)&nextId, sizeof(nextId));
    file.write((const char *)users, sizeof(users));
    return file.good();
}

bool UserStorage::loadFromBinaryFile(const char *fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.read((char *)&count, sizeof(count));
    file.read((char *)&nextId, sizeof(nextId));
    file.read((char *)users, sizeof(users));
    return file.good();
}
