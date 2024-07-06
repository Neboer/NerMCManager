#include "backend.h"
#include <algorithm>

namespace NerMCManager
{

    EnvPack Backend::create_env_pack(fs::path new_ep_dir)
    {
        // parse ep_info.json, get name
        fs::path new_ep_info_path = new_ep_dir / "ep_info.json";
        json new_ep_info_json = parse_json_file(new_ep_info_path);
        EnvPack new_ep = EnvPack::parse_from_json(new_ep_info_json);

        // find if new_ep's fs name is in env pack names.
        str new_ep_fs_name = new_ep.get_fs_name();
        std::vector<str> ep_names = get_env_pack_names();
        if (std::find(ep_names.begin(), ep_names.end(), new_ep_fs_name) != ep_names.end())
        {
            // find new_ep's fs name in env pack names. already exists.
            throw std::runtime_error("Env pack already exists.");
        }

        // ep does not exist, copy new_ep_dir to cached_ep_dir
        fs::path new_ep_target_dir = get_cached_ep_dir() / new_ep_fs_name;
        fs::copy(new_ep_dir, new_ep_target_dir, fs::copy_options::recursive);
        return new_ep;
    }


    void Backend::delete_env_pack(str ep_name, str ep_version)
    {
        // find if ep_name-ep_version exists in env pack names.
        str ep_fs_name = ep_name + "-" + ep_version;
        std::vector<str> ep_names = get_env_pack_names();
        if (std::find(ep_names.begin(), ep_names.end(), ep_fs_name) == ep_names.end())
        {
            // find ep_name-ep_version in env pack names. does not exist.
            throw std::runtime_error("Env pack does not exist.");
        }

        // ep exists, delete it.
        fs::path ep_dir = get_cached_ep_dir() / ep_fs_name;
        fs::remove_all(ep_dir);
    }


    EnvPack Backend::rename_env_pack(str ep_name, str ep_version, str new_ep_name, str new_ep_version)
    {
        // find if ep_name-ep_version exists in env pack names.
        str ep_fs_name = ep_name + "-" + ep_version;
        std::vector<str> ep_names = get_env_pack_names();
        if (std::find(ep_names.begin(), ep_names.end(), ep_fs_name) == ep_names.end())
        {
            // find ep_name-ep_version in env pack names. does not exist.
            throw std::runtime_error("Env pack does not exist.");
        }

        // find if new_ep_name-new_ep_version exists in env pack names.
        str new_ep_fs_name = new_ep_name + "-" + new_ep_version;
        if (std::find(ep_names.begin(), ep_names.end(), new_ep_fs_name) != ep_names.end())
        {
            // find new_ep_name-new_ep_version in env pack names. already exists.
            throw std::runtime_error("New env pack already exists.");
        }

        // change ep_info.json name and version before renaming.
        fs::path ep_dir = get_cached_ep_dir() / ep_fs_name;
        json ep_info = parse_json_file(ep_dir / "ep_info.json");
        ep_info["name"] = new_ep_name;
        ep_info["version"] = new_ep_version;
        
        // rename directory
        fs::path new_ep_dir = get_cached_ep_dir() / new_ep_fs_name;
        fs::rename(ep_dir, new_ep_dir);

        // update content of ep_info.json
        write_json_file(new_ep_dir / "ep_info.json", ep_info);

        return EnvPack::parse_from_json(ep_info);
    }

    std::vector<EnvPack> Backend::get_env_packs()
    {
        std::vector<EnvPack> env_packs;
        std::vector<str> ep_names = get_env_pack_names();
        for (str ep_fs_name : ep_names)
        {
            fs::path ep_dir = get_cached_ep_dir() / ep_fs_name;
            json ep_info = parse_json_file(ep_dir / "ep_info.json");
            env_packs.push_back(EnvPack::parse_from_json(ep_info));
        }
        return env_packs;
    }

    std::vector<str> Backend::get_env_pack_names()
    {
        std::vector<str> ep_names;
        for (const auto &entry : fs::directory_iterator(get_cached_ep_dir()))
        {
            if (entry.is_directory())
            {
                ep_names.push_back(entry.path().filename());
            }
        }
        return ep_names;
    }
}