#pragma once

class User
{
private:
    int id_user;
    char fullName[100];
    char email[100];
    unsigned long password;
    char number[15];
    char address[150];

public:
    User();
    User(int id_user, const char *fullName, const char *email,
         const char *password, const char *number,
         const char *address);

    int getId() const;
    const char *getFullName() const;
    const char *getEmail() const;

    void setId(int id);
    void setFullName(const char *name);
    void setEmail(const char *email);

    void setPassword(const char *password);
    bool checkPassword(const char *password) const;
};
