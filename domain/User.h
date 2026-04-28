#pragma once
using namespace std;

class User
{
private:
    int id_user;
    char fullName[100];
    char email[100];
    char password[8];
    char number[12];
    char address[150];

public:
    User();
    User(int id_user, const char *fullName, const char *email,
         const char *password, const char *number,
         const char *address);

    int getId() const;
    const char *getFullName() const;
    const char *getEmail() const;

    void setFullName(const char *name);
    void setEmail(const char *email);
};
