#pragma once

#include "../../domain/Product.h"

class ProductStorage
{
private:
    const char *FILE_NAME = "products.dat";

public:
    void add(Product &product);

    int getAll(Product products[], int maxCount);

    bool getById(int id, Product &result);

    bool update(const Product &updatedProduct);

    bool deleteProduct(int id);
};
