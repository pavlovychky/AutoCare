#include "OrderService.h"

void OrderService::createOrderFromCart(int userId)
{
    Cart cart;

    if (!cartStorage.getByUserId(userId, cart))
        return;

    Order order;
    order.setId(0); 

    for (int i = 0; i < cart.getProductCount(); i++)
    {
        order.addProduct(cart.getProduct(i));
    }

    orderStorage.add(order);

    cart.clearCart();
    cartStorage.update(cart);
}
