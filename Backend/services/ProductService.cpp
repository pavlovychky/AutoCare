#include "ProductService.h"

ProductService::ProductService(ProductStorage *productStorage, CategoryStorage *categoryStorage)
{
    this->productStorage = productStorage;
    this->categoryStorage = categoryStorage;
}

Product *ProductService::createProduct(const User *admin, int categoryId, const char *article,
                                       const char *name, const char *brand, int price, int quantity)
{
    if (admin == 0 || !admin->isAdmin() || categoryStorage->getById(categoryId) == 0 || price <= 0 || quantity < 0)
    {
        return 0;
    }

    return productStorage->create(categoryId, article, name, brand, price, quantity);
}

bool ProductService::addCarMarkToProduct(const User *admin, int productId, const char *carMark)
{
    if (admin == 0 || !admin->isAdmin())
    {
        return false;
    }

    Product *product = productStorage->getById(productId);
    if (product == 0)
    {
        return false;
    }

    return product->addCarMark(carMark);
}

Product *ProductService::searchByArticle(const char *article)
{
    return productStorage->getByArticle(article);
}

int ProductService::searchByBrand(const char *brand, Product *result[], int maxResult)
{
    return productStorage->getByBrand(brand, result, maxResult);
}

int ProductService::searchByCarMark(const char *carMark, Product *result[], int maxResult)
{
    return productStorage->getByCarMark(carMark, result, maxResult);
}
