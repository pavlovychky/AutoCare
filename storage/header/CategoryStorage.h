#pragma once

#include "../../domain/Category.h"

class CategoryStorage
{
private:
    const char *FILE_NAME = "categories.dat";

public:
    void add(Category &category);

    int getAll(Category categories[], int maxCount);

    bool getById(int id, Category &result);

    bool update(const Category &updatedCategory);

    bool deleteCategory(int id);
};
