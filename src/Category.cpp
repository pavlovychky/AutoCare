#include <iostream>
#include "../domain/Category.h"
#include "Category.h"

Category::Category()
{
    name[0] = '\0';
    about[0] = '\0';
    id = 0;
}

Category::Category(const char *name, const char *about)
{
    strcpy(this->name, name);
    strcpy(this->about, about);
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
    strcpy(this->name, name);
}

void Category::setAbout(const char *about){
    strcpy(this->about,about);
}