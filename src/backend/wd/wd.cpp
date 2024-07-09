#include "wd.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

WorldData::WorldData(str team_name, str ep_name, int world_id, std::vector<str> additional_paths)
    : team_name(team_name), ep_name(ep_name), world_id(world_id), additional_paths(additional_paths) {}

WorldData WorldData::parse_from_json(const json &wd_json)
{
    str team_name = wd_json.at("team_name");
    str ep_name = wd_json.at("ep_name");
    int world_id = wd_json.at("world_id");
    std::vector<str> additional_paths = wd_json.at("additional_paths").get<std::vector<str>>();

    return WorldData(team_name, ep_name, world_id, additional_paths);
}

json WorldData::to_json() const
{
    json wd_json;
    wd_json["team_name"] = team_name;
    wd_json["ep_name"] = ep_name;
    wd_json["world_id"] = world_id;
    wd_json["additional_paths"] = additional_paths;

    return wd_json;
}

str WorldData::get_fs_name() const
{
    return generate_id(team_name, ep_name, world_id);
}

str WorldData::generate_id(const str &team_name, const str &ep_name, int world_id)
{
    std::ostringstream oss;
    oss << team_name << "-" << ep_name << "-" << world_id;
    return oss.str();
}

void WorldData::pack(const str &output_path) const
{
    str tar_command = "tar -czf " + output_path + " ";
    tar_command += team_name + "-" + ep_name + "-" + std::to_string(world_id);
    
    for (const auto &path : additional_paths)
    {
        tar_command += " " + path;
    }

    system(tar_command.c_str());
}

void WorldData::unpack(const str &input_path)
{
    str tar_command = "tar -xzf " + input_path;
    system(tar_command.c_str());
}
