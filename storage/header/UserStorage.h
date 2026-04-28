#include "../domain/User.h"

class UserStorage {
public:
    static void addUser(const User& user);
    static int getAllUsers(User users[], int maxCount);
    static bool findUserById(int id_user, User& result);
    static bool updateUser(const User& user);
    static bool deleteUser(int id_user);
};