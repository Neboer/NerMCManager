#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>

namespace NerMCManager
{
    void init_db(std::string db_path);
}