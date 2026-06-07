#include "../domain/Category.h"
#include "../include/Utils.h"
#include <cstring>

Category::Category()
{
    id = 0;

    name[0] = '\0';
    about[0] = '\0';
}

Category::Category(const char *name, const char *about)
{
    utils::CopyString(this->name, name, sizeof(this->name));
    utils::CopyString(this->about, about, sizeof(this->about));
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
    utils::CopyString(this->name, name, sizeof(this->name));
}

void Category::setAbout(const char *about){
    utils::CopyString(this->about, about, sizeof(this->about));
}

int Category::getId() const
{
    return id;
}

void Category::setId(int id)
{
    this->id = id;
}
