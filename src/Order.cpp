#include "../domain/Order.h"
#include "../include/Utils.h"

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

    utils::CopyString(this->orderDate, orderDate, sizeof(this->orderDate));
    utils::CopyString(this->delivery, deliveryAddress, sizeof(this->delivery));
    utils::CopyString(this->status, status, sizeof(this->status));

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

void Order::setId(int id)
{
    this->id_order = id;
}

int Order::getUserId() const
{
    return userId;
}
void Order::setUserId(int userId)
{
    this->userId = userId;
}
void Order::setTotal(double total)
{
    this->total = total;
}

const char *Order::getOrderDate() const
{
    return orderDate;
}

void Order::setOrderDate(const char *date)
{
    utils::CopyString(orderDate, date, sizeof(orderDate));
}