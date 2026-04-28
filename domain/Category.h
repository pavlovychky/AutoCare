#pragma once
using namespace std;

class Category
{
private:
    char name[100];
    char about[200];
    int id;

public:
    Category();
    Category(const char *name, const char *about);

    const char *getName() const;
    const char *getAbout() const;

    void setName(const char *name);
    void setAbout(const char *about)
};
