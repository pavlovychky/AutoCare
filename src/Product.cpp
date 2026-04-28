#include <iostream>
#include "../domain/Product.h"
#include "Product.h"

Product::Product()
{
    id_prod = 0;
    name[0] = '\0';
    character[0] = '\0';
    article[0] = '\0';
    brand[0] = '\0';
    price = 0;
    unit[0] = '\0';
    count = 0;
}

Product::Product(int id_prod, const char *name, const char *character, const char *article, const char *brand, double price, const char *unit, int count)
{
    this->id_prod = id_prod;
    strcpy(this->name, name);
    strcpy(this->character, character);
    strcpy(this->article, article);
    strcpy(this->brand, brand);
    this->price, price;
    strcpy(this->unit, unit);
    this->count = count;
}

int Product::getId_prod() const
{
    return id_prod;
}

const char *Product::getName() const
{
    return name;
}

double Product::getPrice() const
{
    return price;
}

void Product::setPrice(double price)
{
    if (price)
    {
        this->price, price, sizeof(this->price) - 1;
        this->price[sizeof(this->price) - 1] = 0;
    }
    else
    {
        this->price = 0;
    }
}

void Product::setCount(int count)
{
    if (count)
    {
        this->count, count, sizeof(count) - 1;
        this->count[sizeof(this->count) - 1] = 0;
    }
    else
    {
        this->count = 0;
    }
}
