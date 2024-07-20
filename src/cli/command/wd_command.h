#pragma once

#include <nlohmann/json.hpp>
#include <argparse/argparse.hpp>
using json = nlohmann::json;
using str = std::string;

json handle_wd_command(const str& subcommand, const str& path, const str& new_wd_name);
