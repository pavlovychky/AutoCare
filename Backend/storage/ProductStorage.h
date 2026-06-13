#pragma once

#include "../domain/Product.h"

class ProductStorage
{
private:
    Product products[MAX_PRODUCTS];
    int count;
    int nextId;

public:
    ProductStorage();

    Product *create(int categoryId, const char *article, const char *name,
                    const char *brand, int price, int quantity);
    Product *getById(int id);
    Product *getByIndex(int index);
    Product *getByArticle(const char *article);
    int getByBrand(const char *brand, Product *result[], int maxResult);
    int getByCarMark(const char *carMark, Product *result[], int maxResult);
    bool update(const Product &product);
    bool remove(int id);

    int getCount() const;
    bool saveToBinaryFile(const char *fileName) const;
    bool loadFromBinaryFile(const char *fileName);
};
