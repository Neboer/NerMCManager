#pragma once
#include <string>
#include "../../common/variables.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using str = std::string;

namespace NerMCManager
{
    class EnvPack
    {
    public:
        str name;
        str version;

        str game_version;
        ModPlatform mod_platform;
        str mod_platform_version;
        str java_version;
        str startup_output;

        EnvPack(str name, str version, str game_version, ModPlatform mod_platform, str mod_platform_version, str java_version, str startup_output);
        static EnvPack parse_from_json(json ep_json);
        json to_json();

        str get_fs_name();
    };
}