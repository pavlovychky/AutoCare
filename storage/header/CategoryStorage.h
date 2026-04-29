#pragma once
#include "../domain/Category.h"

class CategoryStorage
{
public:
    static void addCategory(const Category &category);
    static int getAllCategories(Category categories[], int maxCount);
    static bool findCategoryById(int id, Category &result);
    static bool updateCategory(const Category &updatedCategory);
    static bool deleteCategory(int id);
}