#include "ep.h"


namespace NerMCManager
{
    EnvPack::EnvPack(str name, str version, str game_version, ModPlatform mod_platform, str mod_platform_version, str java_version, str startup_output)
    {
        this->name = name;
        this->version = version;
        this->game_version = game_version;
        this->mod_platform = mod_platform;
        this->mod_platform_version = mod_platform_version;
        this->java_version = java_version;
        this->startup_output = startup_output;
    }

    EnvPack EnvPack::parse_from_json(json ep_json)
    {
        str name = ep_json["name"];
        str version = ep_json["version"];
        str game_version = ep_json["game_version"];
        ModPlatform mod_platform = StringToModPlatform(ep_json["mod_platform"]);
        str mod_platform_version = ep_json["mod_platform_version"];
        str java_version = ep_json["java_version"];
        str startup_output = ep_json["startup_output"];
        return EnvPack(name, version, game_version, mod_platform, mod_platform_version, java_version, startup_output);
    }

    str EnvPack::get_fs_name()
    {
        return this->name + "-" + this->version;
    }

}