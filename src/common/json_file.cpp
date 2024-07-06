#include "json_file.h"

namespace NerMCManager
{
    json parse_json_file(fs::path file_path)
    {
        std::ifstream f(file_path);
        json data = json::parse(f);
        f.close();
        return data;
    }

    void write_json_file(fs::path file_path, json data)
    {
        std::ofstream o(file_path);
        o << std::setw(4) << data << std::endl;
        o.close();
    }
}