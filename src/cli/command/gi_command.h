#pragma once

#include <nlohmann/json.hpp>
#include <argparse/argparse.hpp>
using json = nlohmann::json;
using str = std::string;

json handle_gi_command(const str& subcommand);
