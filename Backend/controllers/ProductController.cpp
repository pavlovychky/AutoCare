#include "ProductController.h"
#include <cstdlib>
#include <string>

ProductController::ProductController(
    ProductService& service,
    ProductStorage& storage,
    UserStorage& users)
    : productService(service),
      productStorage(storage),
      userStorage(users)
{
}

crow::json::wvalue ProductController::productToJson(
    const Product* product)
{
    crow::json::wvalue json;

    if (!product)
        return json;

    json["id"] = product->getId();
    json["categoryId"] = product->getCategoryId();
    json["article"] = product->getArticle();
    json["name"] = product->getName();
    json["brand"] = product->getBrand();
    json["price"] = product->getPrice();
    json["quantity"] = product->getQuantity();
    json["active"] = product->isActive();

    crow::json::wvalue carMarks;

    for (int i = 0; i < product->getCarMarkCount(); i++)
    {
        carMarks[i] = product->getCarMark(i);
    }

    json["carMarks"] = std::move(carMarks);

    return json;
}

void ProductController::registerRoutes(crow::SimpleApp& app)
{
    // GET /products
    CROW_ROUTE(app, "/products")
    ([this]()
    {
        crow::json::wvalue result;

        for (int i = 0; i < productStorage.getCount(); i++)
        {
            Product* product =
                productStorage.getByIndex(i);

            result[i] = productToJson(product);
        }

        return result;
    });

    CROW_ROUTE(app, "/api/products")
    ([this]()
    {
        crow::json::wvalue result;
        int jsonIndex = 0;

        for (int i = 0; i < productStorage.getCount(); i++)
        {
            Product* product =
                productStorage.getByIndex(i);

            if (product && product->isActive())
            {
                result[jsonIndex] = productToJson(product);
                jsonIndex++;
            }
        }

        return crow::response(result);
    });

    // GET /products/<id>
    CROW_ROUTE(app, "/products/<int>")
    ([this](int id)
    {
        Product* product =
            productStorage.getById(id);

        if (!product)
        {
            return crow::response(
                404,
                "Product not found");
        }

        return crow::response(
            productToJson(product));
    });

    CROW_ROUTE(app, "/api/products/<int>")
    ([this](int id)
    {
        Product* product =
            productStorage.getById(id);

        if (!product)
        {
            return crow::response(
                404,
                "Product not found");
        }

        return crow::response(
            productToJson(product));
    });

    CROW_ROUTE(app, "/api/products")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req)
    {
        auto body = crow::json::load(req.body);

        if (!body || !body.has("adminId") || !body.has("categoryId") ||
            !body.has("article") || !body.has("name") || !body.has("brand") ||
            !body.has("price") || !body.has("quantity"))
        {
            return crow::response(400, "Invalid product payload");
        }

        User* admin = userStorage.getById(body["adminId"].i());
        if (!admin || !admin->isAdmin())
        {
            return crow::response(403, "Forbidden");
        }

        std::string article = body["article"].s();
        std::string name = body["name"].s();
        std::string brand = body["brand"].s();

        Product* product = productService.createProduct(
            admin,
            static_cast<int>(body["categoryId"].i()),
            article.c_str(),
            name.c_str(),
            brand.c_str(),
            static_cast<int>(body["price"].i()),
            static_cast<int>(body["quantity"].i()));

        if (!product)
        {
            return crow::response(400, "Cannot create product");
        }

        if (body.has("carMark"))
        {
            std::string carMark = body["carMark"].s();
            product->addCarMark(carMark.c_str());
        }

        return crow::response(201, productToJson(product));
    });

    CROW_ROUTE(app, "/api/products/<int>")
    .methods(crow::HTTPMethod::PUT)
    ([this](const crow::request& req, int id)
    {
        auto body = crow::json::load(req.body);

        if (!body || !body.has("adminId"))
        {
            return crow::response(400, "Invalid product payload");
        }

        User* admin = userStorage.getById(body["adminId"].i());
        Product* product = productStorage.getById(id);

        if (!admin || !admin->isAdmin())
        {
            return crow::response(403, "Forbidden");
        }

        if (!product)
        {
            return crow::response(404, "Product not found");
        }

        if (body.has("categoryId"))
            product->setCategoryId(static_cast<int>(body["categoryId"].i()));
        if (body.has("article"))
        {
            std::string article = body["article"].s();
            product->setArticle(article.c_str());
        }
        if (body.has("name"))
        {
            std::string name = body["name"].s();
            product->setName(name.c_str());
        }
        if (body.has("brand"))
        {
            std::string brand = body["brand"].s();
            product->setBrand(brand.c_str());
        }
        if (body.has("price"))
            product->setPrice(static_cast<int>(body["price"].i()));
        if (body.has("quantity"))
            product->setQuantity(static_cast<int>(body["quantity"].i()));
        if (body.has("carMark"))
        {
            std::string carMark = body["carMark"].s();
            product->addCarMark(carMark.c_str());
        }

        productStorage.update(*product);
        return crow::response(productToJson(product));
    });

    CROW_ROUTE(app, "/api/products/<int>")
    .methods(crow::HTTPMethod::Delete)
    ([this](const crow::request& req, int id)
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

        if (!productStorage.remove(id))
        {
            return crow::response(404, "Product not found");
        }

        return crow::response(200, "Product deleted");
    });

    // GET /products/article/<article>
    CROW_ROUTE(app,
               "/products/article/<string>")
    ([this](const std::string& article)
    {
        Product* product =
            productService.searchByArticle(
                article.c_str());

        if (!product)
        {
            return crow::response(
                404,
                "Product not found");
        }

        return crow::response(
            productToJson(product));
    });

    CROW_ROUTE(app,
               "/api/products/search")
    ([this](const crow::request& req)
    {
        std::string q = req.url_params.get("q") ? req.url_params.get("q") : "";
        crow::json::wvalue result;
        int jsonIndex = 0;

        for (int i = 0; i < productStorage.getCount(); i++)
        {
            Product* product = productStorage.getByIndex(i);
            if (!product || !product->isActive())
                continue;

            std::string name = product->getName();
            std::string brand = product->getBrand();
            std::string article = product->getArticle();

            if (q.empty() ||
                name.find(q) != std::string::npos ||
                brand.find(q) != std::string::npos ||
                article.find(q) != std::string::npos)
            {
                result[jsonIndex] = productToJson(product);
                jsonIndex++;
            }
        }

        return crow::response(result);
    });

    // GET /products/brand/<brand>
    CROW_ROUTE(app,
               "/products/brand/<string>")
    ([this](const std::string& brand)
    {
        Product* products[MAX_PRODUCTS];

        int count =
            productService.searchByBrand(
                brand.c_str(),
                products,
                MAX_PRODUCTS);

        crow::json::wvalue result;

        for (int i = 0; i < count; i++)
        {
            result[i] =
                productToJson(products[i]);
        }

        return crow::response(result);
    });

    // GET /products/car/<carMark>
    CROW_ROUTE(app,
               "/products/car/<string>")
    ([this](const std::string& carMark)
    {
        Product* products[MAX_PRODUCTS];

        int count =
            productService.searchByCarMark(
                carMark.c_str(),
                products,
                MAX_PRODUCTS);

        crow::json::wvalue result;

        for (int i = 0; i < count; i++)
        {
            result[i] =
                productToJson(products[i]);
        }

        return crow::response(result);
    });
}
