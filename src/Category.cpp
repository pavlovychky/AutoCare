#include "../domain/Category.h"

Category::Category()
{
    id = 0;

    name[0] = '\0';
    about[0] = '\0';
}

Category::Category(const char *name, const char *about)
{
    strcpy_s(this->name, sizeof(this->name), name);
    strcpy_s(this->about, sizeof(this->about), about);
}

const char *Category::getName() const
{
    return name;
}

const char *Category::getAbout() const
{
    return about;
}

void Category::setName(const char *name)
{
    strcpy_s(this->name, sizeof(this->name), name);
}

void Category::setAbout(const char *about){
    strcpy_s(this->about, sizeof(this->about), about);
}
