#include "ProductStorage.h"
#include <fstream>

ProductStorage::ProductStorage()
{
    count = 0;
    nextId = 1;
}

Product *ProductStorage::create(int categoryId, const char *article, const char *name,
                                const char *brand, int price, int quantity)
{
    if (count >= MAX_PRODUCTS || getByArticle(article) != 0)
    {
        return 0;
    }

    products[count] = Product(nextId, categoryId, article, name, brand, price, quantity);
    count++;
    nextId++;
    return &products[count - 1];
}

Product *ProductStorage::getById(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (products[i].isActive() && products[i].getId() == id)
        {
            return &products[i];
        }
    }

    return 0;
}

Product *ProductStorage::getByIndex(int index)
{
    if (index < 0 || index >= count)
    {
        return 0;
    }

    return &products[index];
}

Product *ProductStorage::getByArticle(const char *article)
{
    for (int i = 0; i < count; i++)
    {
        if (products[i].hasArticle(article))
        {
            return &products[i];
        }
    }

    return 0;
}

int ProductStorage::getByBrand(const char *brand, Product *result[], int maxResult)
{
    int resultCount = 0;
    for (int i = 0; i < count && resultCount < maxResult; i++)
    {
        if (products[i].hasBrand(brand))
        {
            result[resultCount] = &products[i];
            resultCount++;
        }
    }

    return resultCount;
}

int ProductStorage::getByCarMark(const char *carMark, Product *result[], int maxResult)
{
    int resultCount = 0;
    for (int i = 0; i < count && resultCount < maxResult; i++)
    {
        if (products[i].fitsCarMark(carMark))
        {
            result[resultCount] = &products[i];
            resultCount++;
        }
    }

    return resultCount;
}

bool ProductStorage::update(const Product &product)
{
    Product *existing = getById(product.getId());
    if (existing == 0)
    {
        return false;
    }

    *existing = product;
    return true;
}

bool ProductStorage::remove(int id)
{
    Product *product = getById(id);
    if (product == 0)
    {
        return false;
    }

    product->setActive(false);
    return true;
}

int ProductStorage::getCount() const
{
    return count;
}

bool ProductStorage::saveToBinaryFile(const char *fileName) const
{
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.write((const char *)&count, sizeof(count));
    file.write((const char *)&nextId, sizeof(nextId));
    file.write((const char *)products, sizeof(products));
    return file.good();
}

bool ProductStorage::loadFromBinaryFile(const char *fileName)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.read((char *)&count, sizeof(count));
    file.read((char *)&nextId, sizeof(nextId));
    file.read((char *)products, sizeof(products));
    return file.good();
}
