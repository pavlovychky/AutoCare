#pragma once

#include "../storage/ProductStorage.h"
#include "../storage/CategoryStorage.h"
#include "../domain/User.h"

class ProductService
{
private:
    ProductStorage *productStorage;
    CategoryStorage *categoryStorage;

public:
    ProductService(ProductStorage *productStorage, CategoryStorage *categoryStorage);

    Product *createProduct(const User *admin, int categoryId, const char *article,
                           const char *name, const char *brand, int price, int quantity);
    bool addCarMarkToProduct(const User *admin, int productId, const char *carMark);
    Product *searchByArticle(const char *article);
    int searchByBrand(const char *brand, Product *result[], int maxResult);
    int searchByCarMark(const char *carMark, Product *result[], int maxResult);
};
