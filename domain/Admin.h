#pragma once
using namespace std;

class Admin
{
private:
    char username[30];
    unsigned long password;

public:
    Admin();
    Admin(const char *username, unsigned long password);

    const char *getUsername() const;
    unsigned long getPassword() const;
};
