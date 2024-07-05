#include "json_parser.h"

namespace NerMCManager
{
    json parse_json_file(std::string file_path)
    {
        std::ifstream f(file_path);
        json data = json::parse(f);
        return data;
    }
}