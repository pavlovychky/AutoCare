#include <iostream>
#include <limits>

#include "../services/AuthService.h"
#include "../services/CartService.h"
#include "../services/OrderService.h"
#include "../storage/header/ProductStorage.h"

using namespace std;

void pause()
{
    cout << "\nPress Enter...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    AuthService authService;
    CartService cartService;
    OrderService orderService;
    ProductStorage productStorage;

    int choice;
    bool loggedIn = false;
    int userId = -1;

    char email[100];
    char password[30];

    while (true)
    {
        cout << "\n========= AUTOCARE =========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Show products\n";
        cout << "4. Add to cart\n";
        cout << "5. View cart total\n";
        cout << "6. Create order\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;

        if (cin.fail())
        {
            clearInput();
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            char fullName[100], number[20], address[150];

            cout << "Full name: ";
            clearInput();
            cin.getline(fullName, 100);

            cout << "Email: ";
            cin.getline(email, 100);

            cout << "Password: ";
            cin.getline(password, 30);

            cout << "Phone: ";
            cin.getline(number, 20);

            cout << "Address: ";
            cin.getline(address, 150);

            if (authService.registerUser(fullName, email, password, number, address))
                cout << "Registered successfully!\n";
            else
                cout << "Email already exists!\n";

            pause();
            break;
        }

        case 2:
        {
            cout << "Email: ";
            clearInput();
            cin.getline(email, 100);

            cout << "Password: ";
            cin.getline(password, 30);

            userId = authService.loginUser(email, password);

            if (userId != -1)
            {
                loggedIn = true;
                cout << "Login success! ID = " << userId << "\n";
            }
            else
            {
                cout << "Wrong credentials!\n";
            }

            pause();
            break;
        }

        case 3:
        {
            Product products[100];
            int count = productStorage.getAll(products, 100);

            for (int i = 0; i < count; i++)
            {
                cout << products[i].getId_prod()
                     << " | " << products[i].getName()
                     << " | " << products[i].getPrice()
                     << "\n";
            }

            pause();
            break;
        }

        case 4:
        {
            if (!loggedIn)
            {
                cout << "Login first!\n";
                pause();
                break;
            }

            int productId;
            cout << "Product ID: ";
            cin >> productId;

            Product p;

            if (productStorage.getById(productId, p))
            {
                cartService.addToCart(userId, p);
                cout << "Added to cart!\n";
            }
            else
            {
                cout << "Product not found!\n";
            }

            pause();
            break;
        }

        case 5:
        {
            if (!loggedIn)
            {
                cout << "Login first!\n";
                pause();
                break;
            }

            cout << "Cart total: "
                 << cartService.getTotal(userId)
                 << "\n";

            pause();
            break;
        }

        case 6:
        {
            if (!loggedIn)
            {
                cout << "Login first!\n";
                pause();
                break;
            }

            orderService.createOrderFromCart(userId);

            cout << "Order created!\n";
            pause();
            break;
        }

        case 0:
            return 0;

        default:
            cout << "Invalid option!\n";
            pause();
        }
    }
}
