#include "Utils.h"
#include <cstring>

void utils::CopyString(char *destination, const char *source, int size)
{
    if (destination == 0 || size <= 0)
    {
        return;
    }

    if (source == 0)
    {
        destination[0] = '\0';
        return;
    }

    std::strncpy(destination, source, size - 1);
    destination[size - 1] = '\0';
}

unsigned long utils::Hash(const char *text)
{
    unsigned long hash = 2166136261u;
    const unsigned long prime = 16777619u;
    const char salt[] = "AutoPartsCourse";

    for (int i = 0; salt[i] != '\0'; i++)
    {
        hash ^= (unsigned char)salt[i];
        hash *= prime;
    }

    if (text != 0)
    {
        for (int i = 0; text[i] != '\0'; i++)
        {
            hash ^= (unsigned char)text[i];
            hash *= prime;
        }
    }

    return hash;
}
