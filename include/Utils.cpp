#include "../include/Utils.h"

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
}
