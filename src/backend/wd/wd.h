#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using str = std::string;

class WorldData
{
public:
    WorldData(str team_name, str ep_name, int world_id, std::vector<str> additional_paths);

    static WorldData parse_from_json(const json &wd_json);
    json to_json() const;
    str get_fs_name() const;

    void pack(const str &output_path) const;
    void unpack(const str &input_path);

private:
    str team_name;
    str ep_name;
    int world_id;
    std::vector<str> additional_paths;

    static str generate_id(const str &team_name, const str &ep_name, int world_id);
};
