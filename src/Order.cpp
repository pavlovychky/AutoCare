#include "../domain/Order.h"

Order::Order()
{
    id_order = 0;
    userId = 0;
    total = 0;
    productCount = 0;

    orderDate[0] = '\0';
    delivery[0] = '\0';
    status[0] = '\0';
}

Order::Order(int id_order, int userId, const char *orderDate, const char *deliveryAddress, const char *status, double totalAmount)
{
    this->id_order = id_order;
    this->userId = userId;
    this->total = totalAmount;

    strcpy_s(this->orderDate, sizeof(this->orderDate), orderDate);
    strcpy_s(this->delivery, sizeof(this->delivery), deliveryAddress);
    strcpy_s(this->status, sizeof(this->status), status);

    this->productCount = 0;
}

int Order::getId() const
{
    return id_order;
}

double Order::getTotal() const
{
    return total;
}

void Order::addProduct(const Product &product)
{
    if (productCount < 50)
    {
        products[productCount] = product;
        productCount++;
    }
}

int Order::getId() const
{
    return id_order;
}

void Order::setId(int id)
{
    this->id_order = id;
}
