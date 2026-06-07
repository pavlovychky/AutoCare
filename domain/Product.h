#pragma once
#include "Category.h"

class Product
{
private:
    int id_prod;
    char name[100];
    Category category;
    char mark[50];
    char character[200];
    char article[50];
    char brand[50];
    double price;
    char unit[20];
    int count;

public:
    Product();
    Product(int id_prod, const char *name, const Category &category, const char *mark, const char *character,
            const char *article, const char *brand,
            double price, const char *unit, int count);

    int getId_prod() const;
    const char *getName() const;
    double getPrice() const;
    int getCount() const;
    Category getCategory() const;
    int getId() const;

    void setId(int id);
    void setPrice(double price);
    void setCount(int count);
};
