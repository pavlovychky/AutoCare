#pragma once

#include "../domain/Category.h"

class CategoryStorage
{
private:
    Category categories[MAX_CATEGORIES];
    int count;
    int nextId;

public:
    CategoryStorage();

    Category *create(const char *name);
    Category *getById(int id);
    Category *getByIndex(int index);
    bool update(const Category &category);
    bool remove(int id);

    int getCount() const;
    bool saveToBinaryFile(const char *fileName) const;
    bool loadFromBinaryFile(const char *fileName);
};
