#pragma once

#include <nlohmann/json.hpp>
#include <argparse/argparse.hpp>
using json = nlohmann::json;
using str = std::string;

json handle_ep_command(const str& subcommand, const str& path, const str& name, const str& version, const str& new_name, const str& new_version);
