#include <ctime>
#include <cstdio>
#include "../services/OrderService.h"

void OrderService::createOrderFromCart(int userId)
{
    Cart cart;

    if (!cartStorage.getByUserId(userId, cart))
    {
        return;
    }

    if (cart.getProductCount() == 0)
    {
        return;
    }

    Order order;

    order.setUserId(userId);

    double total = 0;

    for (int i = 0; i < cart.getProductCount(); i++)
    {
        Product product = cart.getProduct(i);

        order.addProduct(product);

        total += product.getPrice();
    }

    time_t now = time(NULL);

    tm *currentTime = localtime(&now);

    char date[20];

    sprintf(
        date,
        "%02d.%02d.%04d %02d:%02d",
        currentTime->tm_mday,
        currentTime->tm_mon + 1,
        currentTime->tm_year + 1900,
        currentTime->tm_hour,
        currentTime->tm_min);

    order.setOrderDate(date);

    order.setTotal(total);

    orderStorage.add(order);

    cart.clearCart();

    cartStorage.update(cart);
}
