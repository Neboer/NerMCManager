#include "wd_command.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

json handle_wd_command(const str& subcommand, const str& path, const str& new_wd_name) {
    json jsonData;

    try {
        if (subcommand == "list") {
            jsonData["type"] = "get_world_data";
        } else if (subcommand == "import") {
            jsonData["type"] = "import_wd";
            jsonData["args"]["new_ed_dir"] = path;
            jsonData["args"]["wd_name"] = new_wd_name;
        } else {
            std::cerr << "Unexpected subcommand for wd: " << subcommand << std::endl;
            jsonData["error"] = "Invalid subcommand";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return jsonData;
}
