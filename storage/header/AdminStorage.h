#pragma once

#include "../domain/Admin.h"

class AdminStorage
{
private:
    const char* FILE_NAME = "admin.dat";

public:
    bool Save(const Admin& admin);

    bool Get(Admin& admin);

    bool Update(const Admin& admin);
};
