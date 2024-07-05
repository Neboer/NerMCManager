#include "ep_config.h"

namespace NerMCManager
{
    EpConfig parse_ep_config(str config_path)
    {
        json config = parse_json_file(config_path);
        EpConfig ep_config;
        ep_config.name = config["name"];
        ep_config.version = config["version"];
        ep_config.game_version = config["game_version"];
        if (config["mod_platform"] == "forge")
        {
            ep_config.mod_platform = ModPlatform::Forge;
        }
        else if (config["mod_platform"] == "fabric")
        {
            ep_config.mod_platform = ModPlatform::Fabric;
        }
        else if (config["mod_platform"] == "bukkit")
        {
            ep_config.mod_platform = ModPlatform::Bukkit;
        }
        if (config["mod_platform"] == "none")
        {
            ep_config.mod_platform = ModPlatform::None;
        }
        else
        {
            throw std::invalid_argument("mod_platform must be either forge or fabric");
        }
        ep_config.mod_platform_version = config["mod_platform_version"];
        ep_config.java_version = config["java_version"];
        ep_config.startup_output = config["startup_output"];
        return ep_config;
    }
}