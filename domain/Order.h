#pragma once
#include "Product.h"

class Order
{
private:
    int id_order;
    int userId;
    char orderDate[20];
    char delivery[150];
    Product products[50];
    int productCount;
    char status[30];
    double total;

public:
    Order();
    Order(int id_order, int userId, const char *orderDate,
          const char *deliveryAddress, const char *status, double totalAmount);

    int getId() const;
    double getTotal() const;

    void addProduct(const Product &product);
}
