#include <iostream>
#include "../domain/Product.h"

Product::Product()
{
    id_prod = 0;
    price = 0;
    count = 0;

    name[0] = '\0';
    mark[0] = '\0';
    character[0] = '\0';
    article[0] = '\0';
    brand[0] = '\0';
    unit[0] = '\0';
}

Product::Product(int id_prod, const char *name, const char *mark, const char *character, const char *article, const char *brand, double price, const char *unit, int count)
{
    this->id_prod = id_prod;
    this->price = price;
    this->count = count;
    strcpy_s(this->name, sizeof(this->name), name);
    strcpy_s(this->mark, sizeof(this->mark), mark);
    strcpy_s(this->character, sizeof(this->character), character);
    strcpy_s(this->article, sizeof(this->article), article);
    strcpy_s(this->brand, sizeof(this->brand), brand);
    strcpy_s(this->unit, sizeof(this->unit), unit);
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
    this->price = price;
}

void Product::setCount(int count)
{
    this->count = count;
}
