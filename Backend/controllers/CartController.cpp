#include "CartController.h"

CartController::CartController(
    CartService& service,
    CartStorage& storage,
    ProductStorage& prodStorage,
    UserStorage& users)
    : cartService(service),
      cartStorage(storage),
      productStorage(prodStorage),
      userStorage(users)
{
}

crow::json::wvalue CartController::cartToJson(
    const Cart* cart)
{
    crow::json::wvalue json;

    if (!cart)
        return json;

    json["id"] = cart->getId();
    json["userId"] = cart->getUserId();
    json["active"] = cart->isActive();

    crow::json::wvalue items;

    for (int i = 0; i < cart->getItemCount(); i++)
    {
        CartItem item = cart->getItem(i);
        Product* product = productStorage.getById(item.getProductId());

        items[i]["productId"] =
            item.getProductId();

        items[i]["quantity"] =
            item.getQuantity();

        if (product)
        {
            items[i]["name"] = product->getName();
            items[i]["brand"] = product->getBrand();
            items[i]["price"] = product->getPrice();
            items[i]["subtotal"] = product->getPrice() * item.getQuantity();
        }
    }

    json["items"] = std::move(items);
    json["total"] = cartService.calculateTotal(cart);

    return json;
}

void CartController::registerRoutes(
    crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/cart/<int>")
    ([this](int userId)
    {
        Cart* cart =
            cartStorage.getByUserId(userId);

        if (!cart)
        {
            return crow::response(
                404,
                "Cart not found");
        }

        return crow::response(
            cartToJson(cart));
    });

    CROW_ROUTE(app, "/api/cart/<int>")
    ([this](int userId)
    {
        Cart* cart =
            cartStorage.getByUserId(userId);

        if (!cart)
        {
            return crow::response(
                404,
                "Cart not found");
        }

        return crow::response(
            cartToJson(cart));
    });

    CROW_ROUTE(app, "/cart/add")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body =
            crow::json::load(req.body);

        if (!body)
        {
            return crow::response(
                400,
                "Invalid JSON");
        }

        int userId =
            body["userId"].i();

        int productId =
            body["productId"].i();

        int quantity =
            body["quantity"].i();

        User* user =
            userStorage.getById(userId);

        if (!user)
        {
            return crow::response(
                404,
                "User not found");
        }

        bool result =
            cartService.addProduct(
                user,
                productId,
                quantity);

        if (!result)
        {
            return crow::response(
                400,
                "Cannot add product");
        }

        return crow::response(
            200,
            "Product added");
    });

    CROW_ROUTE(app, "/api/cart/add")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body =
            crow::json::load(req.body);

        if (!body || !body.has("userId") || !body.has("productId"))
        {
            return crow::response(
                400,
                "Invalid cart payload");
        }

        int userId =
            body["userId"].i();

        int productId =
            body["productId"].i();

        int quantity =
            body.has("quantity") ? body["quantity"].i() : 1;

        User* user =
            userStorage.getById(userId);

        if (!user)
        {
            return crow::response(
                404,
                "User not found");
        }

        bool result =
            cartService.addProduct(
                user,
                productId,
                quantity);

        if (!result)
        {
            return crow::response(
                400,
                "Cannot add product");
        }

        Cart* cart = cartStorage.getByUserId(userId);
        return crow::response(200, cartToJson(cart));
    });

    CROW_ROUTE(app, "/cart/remove")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body =
            crow::json::load(req.body);

        if (!body)
        {
            return crow::response(
                400,
                "Invalid JSON");
        }

        int userId =
            body["userId"].i();

        int productId =
            body["productId"].i();

        User* user =
            userStorage.getById(userId);

        if (!user)
        {
            return crow::response(
                404,
                "User not found");
        }

        bool result =
            cartService.removeProduct(
                user,
                productId);

        if (!result)
        {
            return crow::response(
                400,
                "Cannot remove product");
        }

        return crow::response(
            200,
            "Product removed");
    });

    CROW_ROUTE(app, "/api/cart/remove")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body =
            crow::json::load(req.body);

        if (!body || !body.has("userId") || !body.has("productId"))
        {
            return crow::response(
                400,
                "Invalid cart payload");
        }

        int userId =
            body["userId"].i();

        int productId =
            body["productId"].i();

        User* user =
            userStorage.getById(userId);

        if (!user)
        {
            return crow::response(
                404,
                "User not found");
        }

        bool result =
            cartService.removeProduct(
                user,
                productId);

        if (!result)
        {
            return crow::response(
                400,
                "Cannot remove product");
        }

        Cart* cart = cartStorage.getByUserId(userId);
        return crow::response(200, cartToJson(cart));
    });

    CROW_ROUTE(app, "/cart/total/<int>")
    ([this](int userId)
    {
        Cart* cart =
            cartStorage.getByUserId(userId);

        if (!cart)
        {
            return crow::response(
                404,
                "Cart not found");
        }

        crow::json::wvalue json;

        json["total"] =
            cartService.calculateTotal(cart);

        return crow::response(json);
    });

    CROW_ROUTE(app, "/api/cart/total/<int>")
    ([this](int userId)
    {
        Cart* cart =
            cartStorage.getByUserId(userId);

        if (!cart)
        {
            return crow::response(
                404,
                "Cart not found");
        }

        crow::json::wvalue json;

        json["total"] =
            cartService.calculateTotal(cart);

        return crow::response(json);
    });
}
