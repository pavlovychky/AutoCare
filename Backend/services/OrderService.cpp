#include "OrderService.h"

OrderService::OrderService(OrderStorage *orderStorage, CartStorage *cartStorage,
                           ProductStorage *productStorage, CartService *cartService)
{
    this->orderStorage = orderStorage;
    this->cartStorage = cartStorage;
    this->productStorage = productStorage;
    this->cartService = cartService;
}

bool OrderService::productsAvailable(const Cart *cart)
{
    for (int i = 0; i < cart->getItemCount(); i++)
    {
        CartItem item = cart->getItem(i);
        Product *product = productStorage->getById(item.getProductId());
        if (product == 0 || product->getQuantity() < item.getQuantity())
        {
            return false;
        }
    }

    return true;
}

void OrderService::decreaseProductQuantity(const Cart *cart)
{
    for (int i = 0; i < cart->getItemCount(); i++)
    {
        CartItem item = cart->getItem(i);
        Product *product = productStorage->getById(item.getProductId());
        if (product != 0)
        {
            product->setQuantity(product->getQuantity() - item.getQuantity());
        }
    }
}

Order *OrderService::createFromCart(const User *user, const char *orderDate,
                                    DeliveryMethod deliveryMethod, const char *deliveryAddress)
{
    if (user == 0 || !user->isClient() || orderDate == 0 || deliveryAddress == 0)
    {
        return 0;
    }

    Cart *cart = cartStorage->getByUserId(user->getId());
    if (cart == 0 || cart->getItemCount() == 0 || !productsAvailable(cart))
    {
        return 0;
    }

    int totalPrice = cartService->calculateTotal(cart);
    Order *order = orderStorage->create(user->getId(), *cart, totalPrice, orderDate, deliveryMethod, deliveryAddress);
    if (order != 0)
    {
        decreaseProductQuantity(cart);
        cart->clear();
    }

    return order;
}

bool OrderService::changeStatus(const User *admin, int orderId, OrderStatus status)
{
    if (admin == 0 || !admin->isAdmin())
    {
        return false;
    }

    Order *order = orderStorage->getById(orderId);
    if (order == 0)
    {
        return false;
    }

    order->setStatus(status);
    return true;
}
