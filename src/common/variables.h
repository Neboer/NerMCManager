#pragma once
#include <string>
#include <unordered_map>

using str = std::string;
namespace NerMCManager
{
    enum ModPlatform
    {
        None = 0,
        Forge = 1,
        Fabric = 2,
        Bukkit = 3
    };

    str ModPlatformToString(ModPlatform platform);
    ModPlatform StringToModPlatform(const str &input_string);
}