#include "../domain/Product.h"
#include "../include/Utils.h"

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

Product::Product(int id_prod, const char *name, const Category &category, const char *mark, const char *character, const char *article, const char *brand, double price, const char *unit, int count)
{
    this->id_prod = id_prod;
    this->category = category;
    this->price = price;
    this->count = count;
    utils::CopyString(this->name, name, sizeof(this->name));
    utils::CopyString(this->mark, mark, sizeof(this->mark));
    utils::CopyString(this->character, character, sizeof(this->character));
    utils::CopyString(this->article, article, sizeof(this->article));
    utils::CopyString(this->brand, brand, sizeof(this->brand));
    utils::CopyString(this->unit, unit, sizeof(this->unit));
}

int Product::getId() const
{
    return id_prod;
}

int Product::getId_prod() const
{
    return id_prod;
}

const char *Product::getName() const
{
    return name;
}

const char *Product::getCharacter() const
{
    return character;
}

const char *Product::getMark() const
{
    return mark;
}

const char *Product::getArticle() const
{
    return article;
}

const char *Product::getBrand() const
{
    return brand;
}

const char *Product::getUnit() const
{
    return unit;
}

double Product::getPrice() const
{
    return price;
}

int Product::getCount() const
{
    return count;
}

Category Product::getCategory() const
{
    return category;
}

void Product::setPrice(double price)
{
    this->price = price;
}

void Product::setCount(int count)
{
    this->count = count;
}

void Product::setId(int id)
{
    this->id_prod = id;
}
