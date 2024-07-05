#pragma once
#include "../config.h"
#include "ep_config.h"
#include "../../common/variables.h"
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <filesystem>

using str = std::string;
using json = nlohmann::json;
namespace fs = std::filesystem;

namespace NerMCManager
{
    class EnvironmentPack
    {
    public:
        str name;
        str version;
        str hash; // hash is calculated from folder's full content. ()

        str game_version;
        ModPlatform mod_platform;
        str mod_platform_version;
        EnvironmentPack(EpConfig ep_config);
        // the process of creating/deleting an ep is not handled here. It is handled in the backend.
        // static EnvironmentPack import_from_path(fs::path ep_path, fs::path backend_ep_dir, );
    };
}