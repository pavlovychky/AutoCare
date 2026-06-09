#pragma once

class Admin
{
private:
    char username[30];
    unsigned long password;

public:
    Admin();
    Admin(const char *username, const char *password);

    const char *getUsername() const;
    unsigned long getPassword() const;

    void setUsername(const char *username);
    void setPassword(const char *password);
};
