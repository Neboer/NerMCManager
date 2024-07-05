#include "init_db.h"

namespace NerMCManager
{
    void init_db(std::string db_path)
    {
        sqlite3 *db;
        int rc = sqlite3_open(db_path.c_str(), &db);
        if (rc)
        {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        char *err_msg = 0;
        rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS env_packs (id INTEGER PRIMARY KEY, name TEXT, version TEXT, game_version TEXT, mod_platform TEXT, mod_platform_version TEXT, java_version TEXT, startup_output TEXT);", 0, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }

        sqlite3_close(db);
    }
}