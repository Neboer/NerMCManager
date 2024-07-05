#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <filesystem>

using str = std::string;
using json = nlohmann::json;
namespace fs = std::filesystem;

namespace NerMCManager
{
    json parse_json_file(fs::path file_path);
}
