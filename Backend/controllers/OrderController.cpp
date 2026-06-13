#include "OrderController.h"
#include <cstdlib>

OrderController::OrderController(OrderService& service,
                                 OrderStorage& storage,
                                 UserStorage& users,
                                 ProductStorage& products)
    : orderService(service),
      orderStorage(storage),
      userStorage(users),
      productStorage(products)
{
}

crow::json::wvalue OrderController::orderToJson(const Order* order)
{
    crow::json::wvalue json;

    if (!order)
        return json;

    json["id"] = order->getId();
    json["userId"] = order->getUserId();
    json["totalPrice"] = order->getTotalPrice();
    json["date"] = order->getOrderDate();
    json["deliveryMethod"] = (int)order->getDeliveryMethod();
    json["deliveryAddress"] = order->getDeliveryAddress();
    json["status"] = (int)order->getStatus();

    User* user = userStorage.getById(order->getUserId());
    if (user)
    {
        json["customerName"] = user->getFullName();
        json["customerEmail"] = user->getEmail();
        json["customerPhone"] = user->getNumber();
    }

    crow::json::wvalue items;
    for (int i = 0; i < order->getItemCount(); i++)
    {
        CartItem item = order->getItem(i);
        Product* product = productStorage.getById(item.getProductId());

        items[i]["productId"] = item.getProductId();
        items[i]["quantity"] = item.getQuantity();

        if (product)
        {
            items[i]["name"] = product->getName();
            items[i]["brand"] = product->getBrand();
            items[i]["price"] = product->getPrice();
        }
    }

    json["items"] = std::move(items);

    return json;
}

void OrderController::registerRoutes(crow::SimpleApp& app)
{
    // GET order by id
    CROW_ROUTE(app, "/orders/<int>")
    ([this](int id)
    {
        Order* order = orderStorage.getById(id);

        if (!order)
            return crow::response(404, "Order not found");

        return crow::response(orderToJson(order));
    });

    CROW_ROUTE(app, "/api/orders")
    ([this](const crow::request& req)
    {
        auto adminParam = req.url_params.get("adminId");
        if (!adminParam)
        {
            return crow::response(400, "adminId is required");
        }

        User* admin = userStorage.getById(std::atoi(adminParam));
        if (!admin || !admin->isAdmin())
        {
            return crow::response(403, "Forbidden");
        }

        crow::json::wvalue json;
        int jsonIndex = 0;

        for (int i = 0; i < orderStorage.getCount(); i++)
        {
            Order* order = orderStorage.getByIndex(i);
            if (order && order->isActive())
            {
                json[jsonIndex] = orderToJson(order);
                jsonIndex++;
            }
        }

        return crow::response(json);
    });

    CROW_ROUTE(app, "/api/orders/<int>")
    ([this](int id)
    {
        Order* order = orderStorage.getById(id);

        if (!order)
            return crow::response(404, "Order not found");

        return crow::response(orderToJson(order));
    });

    // GET orders by user
    CROW_ROUTE(app, "/orders/user/<int>")
    ([this](int userId)
    {
        Order* result[MAX_ORDERS];

        int count = orderStorage.getByUserId(userId, result, MAX_ORDERS);

        crow::json::wvalue json;

        for (int i = 0; i < count; i++)
        {
            json[i] = orderToJson(result[i]);
        }

        return crow::response(json);
    });

    CROW_ROUTE(app, "/api/orders/user/<int>")
    ([this](int userId)
    {
        Order* result[MAX_ORDERS];

        int count = orderStorage.getByUserId(userId, result, MAX_ORDERS);

        crow::json::wvalue json;

        for (int i = 0; i < count; i++)
        {
            json[i] = orderToJson(result[i]);
        }

        return crow::response(json);
    });

    // CREATE order from cart
    CROW_ROUTE(app, "/orders/create")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body = crow::json::load(req.body);

        if (!body)
            return crow::response(400, "Invalid JSON");

        int userId = body["userId"].i();
        std::string date = body["date"].s();
        std::string address = body["address"].s();
        int deliveryMethod = body["deliveryMethod"].i();

        User* user = userStorage.getById(userId);

        if (!user)
            return crow::response(404, "User not found");

        Order* order = orderService.createFromCart(
            user,
            date.c_str(),
            (DeliveryMethod)deliveryMethod,
            address.c_str()
        );

        if (!order)
            return crow::response(400, "Cannot create order");

        return crow::response(orderToJson(order));
    });

    CROW_ROUTE(app, "/api/orders/create")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body = crow::json::load(req.body);

        if (!body || !body.has("userId") || !body.has("date") ||
            !body.has("address") || !body.has("deliveryMethod"))
            return crow::response(400, "Invalid JSON");

        int userId = body["userId"].i();
        std::string date = body["date"].s();
        std::string address = body["address"].s();
        int deliveryMethod = body["deliveryMethod"].i();

        User* user = userStorage.getById(userId);

        if (!user)
            return crow::response(404, "User not found");

        Order* order = orderService.createFromCart(
            user,
            date.c_str(),
            (DeliveryMethod)deliveryMethod,
            address.c_str()
        );

        if (!order)
            return crow::response(400, "Cannot create order");

        return crow::response(201, orderToJson(order));
    });

    // CHANGE STATUS (admin)
    CROW_ROUTE(app, "/orders/status")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body = crow::json::load(req.body);

        if (!body)
            return crow::response(400, "Invalid JSON");

        int adminId = body["adminId"].i();
        int orderId = body["orderId"].i();
        int status = body["status"].i();

        User* admin = userStorage.getById(adminId);

        if (!admin || !admin->isAdmin())
            return crow::response(403, "Forbidden");

        bool ok = orderService.changeStatus(
            admin,
            orderId,
            (OrderStatus)status
        );

        if (!ok)
            return crow::response(400, "Cannot change status");

        return crow::response(200, "Status updated");
    });

    CROW_ROUTE(app, "/api/orders/status")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body = crow::json::load(req.body);

        if (!body || !body.has("adminId") || !body.has("orderId") || !body.has("status"))
            return crow::response(400, "Invalid JSON");

        int adminId = body["adminId"].i();
        int orderId = body["orderId"].i();
        int status = body["status"].i();

        User* admin = userStorage.getById(adminId);

        if (!admin || !admin->isAdmin())
            return crow::response(403, "Forbidden");

        bool ok = orderService.changeStatus(
            admin,
            orderId,
            (OrderStatus)status
        );

        if (!ok)
            return crow::response(400, "Cannot change status");

        Order* order = orderStorage.getById(orderId);
        return crow::response(orderToJson(order));
    });
}
