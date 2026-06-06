#pragma once
#include "Product.h"
using namespace std;

class Cart
{
private:
    int userId;
    Product products[50];
    int productCount;

public:
    Cart();
    Cart(int userId);

    int getUserId() const;
    int getProductCount() const;

    void setUserId(int userId);

    void addProduct(const Product& product);
    void removeProduct(int productId);
    void clearCart();

    Product getProduct(int index) const;

    double getTotal() const;
};
