#include "CategoryStorage.h"
#include <fstream>

CategoryStorage::CategoryStorage()
{
    count = 0;
    nextId = 1;
}

Category *CategoryStorage::create(const char *name)
{
    if (count >= MAX_CATEGORIES)
    {
        return 0;
    }

    categories[count] = Category(nextId, name);
    count++;
    nextId++;
    return &categories[count - 1];
}

Category *CategoryStorage::getById(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (categories[i].isActive() && categories[i].getId() == id)
        {
            return &categories[i];
        }
    }

    return 0;
}

Category *CategoryStorage::getByIndex(int index)
{
    if (index < 0 || index >= count)
    {
        return 0;
    }

    return &categories[index];
}

bool CategoryStorage::update(const Category &category)
{
    Category *existing = getById(category.getId());
    if (existing == 0)
    {
        return false;
    }

    *existing = category;
    return true;
}

bool CategoryStorage::remove(int id)
{
    Category *category = getById(id);
    if (category == 0)
    {
        return false;
    }

    category->setActive(false);
    return true;
}

int CategoryStorage::getCount() const
{
    return count;
}

bool CategoryStorage::saveToBinaryFile(const char *fileName) const
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.write((const char *)&count, sizeof(count));
    file.write((const char *)&nextId, sizeof(nextId));
    file.write((const char *)categories, sizeof(categories));
    return file.good();
}

bool CategoryStorage::loadFromBinaryFile(const char *fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.read((char *)&count, sizeof(count));
    file.read((char *)&nextId, sizeof(nextId));
    file.read((char *)categories, sizeof(categories));
    return file.good();
}
