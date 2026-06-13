#include "CartService.h"

CartService::CartService(CartStorage *cartStorage, ProductStorage *productStorage)
{
    this->cartStorage = cartStorage;
    this->productStorage = productStorage;
}

bool CartService::addProduct(const User *user, int productId, int quantity)
{
    if (user == 0 || !user->isClient() || quantity <= 0)
    {
        return false;
    }

    Product *product = productStorage->getById(productId);
    Cart *cart = cartStorage->getByUserId(user->getId());

    if (product == 0 || cart == 0 || product->getQuantity() < quantity)
    {
        return false;
    }

    return cart->addItem(productId, quantity);
}

bool CartService::removeProduct(const User *user, int productId)
{
    if (user == 0 || !user->isClient())
    {
        return false;
    }

    Cart *cart = cartStorage->getByUserId(user->getId());
    if (cart == 0)
    {
        return false;
    }

    return cart->removeItem(productId);
}

int CartService::calculateTotal(const Cart *cart)
{
    int total = 0;
    if (cart == 0 || !cart->isActive())
    {
        return total;
    }

    for (int i = 0; i < cart->getItemCount(); i++)
    {
        CartItem item = cart->getItem(i);
        Product *product = productStorage->getById(item.getProductId());
        if (product != 0)
        {
            total += product->getPrice() * item.getQuantity();
        }
    }

    return total;
}
