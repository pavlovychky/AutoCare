#pragma once

#include <string>
#include <cstddef>

namespace utils
{
    unsigned long Hash(const std::string &password);

    void CopyString(char *dest, const char *src, size_t size);
};
