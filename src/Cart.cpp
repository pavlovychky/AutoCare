#include "../domain/Cart.h"
#include <cstring>

Cart::Cart()
{
    userId = 0;
    productCount = 0;
}

Cart::Cart(int userId)
{
    this->userId = userId;
    productCount = 0;
}

int Cart::getUserId() const
{
    return userId;
}

int Cart::getProductCount() const
{
    return productCount;
}

void Cart::setUserId(int userId)
{
    this->userId = userId;
}

void Cart::addProduct(const Product &product)
{
    if (productCount < 50)
    {
        products[productCount] = product;
        productCount++;
    }
}

void Cart::removeProduct(int productId)
{
    for (int i = 0; i < productCount; i++)
    {
        if (products[i].getId_prod() == productId)
        {
            for (int j = i; j < productCount - 1; j++)
            {
                products[j] = products[j + 1];
            }
            productCount--;
            break;
        }
    }
}

void Cart::clearCart()
{
    productCount = 0;
}

Product Cart::getProduct(int index) const
{
    return products[index];
}

double Cart::getTotal() const
{
    double sum = 0;
    for (int i = 0; i < productCount; i++)
    {
        sum += products[i].getPrice();
    }
    return sum;
}
