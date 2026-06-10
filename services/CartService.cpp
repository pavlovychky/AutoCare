#include "CartService.h"

void CartService::addToCart(int userId, const Product &product)
{
    Cart cart;

    if (!storage.getByUserId(userId, cart))
    {
        cart.setUserId(userId);
        cart.addProduct(product);

        storage.save(cart); // важливо: save, а не update
        return;
    }

    cart.addProduct(product);

    storage.update(cart);
}

void CartService::removeFromCart(int userId, int productId)
{
    Cart cart;

    if (!storage.getByUserId(userId, cart))
        return;

    cart.removeProduct(productId);
    storage.update(cart);
}
double CartService::getTotal(int userId)
{
    Cart cart;

    if (!storage.getByUserId(userId, cart))
        return 0.0;

    return cart.getTotal();
}
void CartService::clear(int userId)
{
    Cart cart;

    if (!storage.getByUserId(userId, cart))
        return;

    cart.clearCart();
    storage.update(cart);
}
