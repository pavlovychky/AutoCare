#pragma once

#include "../../domain/Admin.h"

class AdminStorage
{
private:
    const char* FILE_NAME = "admin.dat";

public:
    bool save(const Admin &admin);

    bool get(Admin &admin);

    bool update(const Admin &admin);
};
