#include "variables.h"

namespace NerMCManager
{
    str ModPlatformToString(ModPlatform platform)
    {
        switch (platform)
        {
        case None:
            return "None";
        case Forge:
            return "Forge";
        case Fabric:
            return "Fabric";
        case Bukkit:
            return "Bukkit";
        default:
            return "Unknown";
        }
    }

    ModPlatform StringToModPlatform(const std::string &str)
    {
        static const std::unordered_map<std::string, ModPlatform> strToPlatform{
            {"None", None},
            {"Forge", Forge},
            {"Fabric", Fabric},
            {"Bukkit", Bukkit}};

        auto it = strToPlatform.find(str);
        if (it != strToPlatform.end())
        {
            return it->second;
        }
        else
        {
            return None; // 默认值或抛出异常
        }
    }

}