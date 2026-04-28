#pragma once
#include "../domain/Product.h"

class ProductStorage {
public:
    static void addProduct(const Product& product);
    static int getAllProducts(Product products[], int maxCount);
    static bool findProductById(int id, Product& result);
    static bool updateProduct(const Product& updatedProduct);
    static bool deleteProduct(int id);
};