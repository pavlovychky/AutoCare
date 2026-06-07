#include "../include/Utils.h"
#include <cstring>

namespace utils
{
    unsigned long Hash(const std::string &password)
    {
        unsigned long hash = 5381;

        for (char c : password)
        {
            hash = ((hash << 5) + hash) + c;
        }

        return hash;
    }

    void CopyString(char *dest, const char *src, size_t size)
    {
        if (src)
        {
            strncpy(dest, src, size - 1);
            dest[size - 1] = '\0';
        }
        else
        {
            dest[0] = '\0';
        }
    }
}
