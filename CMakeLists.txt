cmake_minimum_required(VERSION 3.10)
project(AutoCare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

set(BACKEND_SOURCES
    Backend/common/Utils.cpp
    Backend/domain/User.cpp
    Backend/domain/Category.cpp
    Backend/domain/Product.cpp
    Backend/domain/Cart.cpp
    Backend/domain/Order.cpp
    Backend/storage/UserStorage.cpp
    Backend/storage/CategoryStorage.cpp
    Backend/storage/ProductStorage.cpp
    Backend/storage/CartStorage.cpp
    Backend/storage/OrderStorage.cpp
    Backend/services/AuthService.cpp
    Backend/services/ProductService.cpp
    Backend/services/CartService.cpp
    Backend/services/OrderService.cpp
    Backend/controllers/AuthController.cpp
    Backend/controllers/ProductController.cpp
    Backend/controllers/CartController.cpp
    Backend/controllers/OrderController.cpp
    Backend/controllers/UserController.cpp
    Backend/controllers/CategoryController.cpp
)

add_executable(AutoCare
    app/main.cpp
    ${BACKEND_SOURCES}
)
target_include_directories(AutoCare PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Backend
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/crow/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/asio/include
)
target_link_libraries(AutoCare PRIVATE Threads::Threads)
