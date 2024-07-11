#include "json_file.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace NerMCManager
{
    json parse_json_file(fs::path file_path)
    {
        std::ifstream f(file_path);
        if (!f.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + file_path.string());
    }

    json data;
    try {
        f >> data;
    } catch (const json::parse_error& e) {
        spdlog::error("JSON parse error: {} at byte position {}", e.what(), e.byte);
        f.close();
        throw std::runtime_error("Failed to parse JSON file: " + str(e.what()));
    } catch (const std::exception& e) {
        spdlog::error("Error reading JSON file: {}", e.what());
        f.close();
        throw;
    }

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