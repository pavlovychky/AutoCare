#pragma once
using namespace std;

class Product
{
private:
    int id_prod;
    char name[100];
    char character[200];
    char article[50];
    char brand[50];
    double price;
    char unit[20];
    int count;

public:
    Product();
    Product(int id_prod, const char *name, const char *character,
            const char *article, const char *brand,
            double price, const char *unit, int count);

    int getId_prod() const;
    const char *getName() const;
    double getPrice() const;

    void setPrice(double price);
    void setCount(int count);
};
