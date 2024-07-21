#include "ep_command.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

json handle_ep_command(const str& subcommand, const str& path, const str& name, const str& version, const str& new_name, const str& new_version) {
    json jsonData;

    try {
        if (subcommand == "list") {
            jsonData["type"] = "get_env_packs";
        } else if (subcommand == "create") {
            jsonData["type"] = "create_env_pack";
            jsonData["args"]["new_ep_dir"] = path;
        } else if (subcommand == "delete") {
            jsonData["type"] = "delete_env_pack";
            jsonData["args"]["ep_name"] = name;
            jsonData["args"]["ep_version"] = version;
        } else if (subcommand == "rename") {
            jsonData["type"] = "rename_env_pack";
            jsonData["args"]["ep_name"] = name;
            jsonData["args"]["ep_version"] = version;
            jsonData["args"]["new_ep_name"] = new_name;
            jsonData["args"]["new_ep_version"] = new_version;
        } else {
            std::cerr << "Unexpected subcommand for ep: " << subcommand << std::endl;
            jsonData["error"] = "Invalid subcommand";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return jsonData;
}
