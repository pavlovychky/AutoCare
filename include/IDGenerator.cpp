#include "IDGenerator.h"

#include <fstream>

int IDGenerator::GetNextId(const char* fileName)
{
    int lastId = 0;

    std::ifstream input(fileName);

    if (input.is_open())
    {
        input >> lastId;
        input.close();
    }

    lastId++;

    std::ofstream output(fileName);

    if (output.is_open())
    {
        output << lastId;
        output.close();
    }

    return lastId;
}