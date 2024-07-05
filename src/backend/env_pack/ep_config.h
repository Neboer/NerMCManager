#pragma once
#include <string>
#include "../common/json_parser.h"
#include "../../common/variables.h"

using str = std::string;

namespace NerMCManager
{
    struct EpConfig {
        str name;
        str version;
        str game_version;
        ModPlatform mod_platform;
        str mod_platform_version;
        str java_version;
        str startup_output;
    };

    EpConfig parse_ep_config(str config_path);
}