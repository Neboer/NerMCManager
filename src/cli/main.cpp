#include <iostream>
#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>
#include "sender.h"
#include "command/ep_command.h"
#include "command/gi_command.h"
#include "command/wd_command.h"

using str = std::string;
using json = nlohmann::json;
namespace fs = std::filesystem;

void splitByHyphen(const str& input, str& left, str& right) {
    size_t hyphenPos = input.find('-');
    if (hyphenPos != str::npos) {
        left = input.substr(0, hyphenPos);
        right = input.substr(hyphenPos + 1);
    } else {
        std::cerr << "No hyphen found in the input string." << std::endl;
    }
}

void print_json(const json& j, int indent = 0) {
    str indent_space(indent, ' ');
    if (j.is_object()) {
        for (auto it = j.begin(); it != j.end(); ++it) {
            std::cout << indent_space << it.key() << ": ";
            print_json(it.value(), indent + 4);
        }
    } else if (j.is_array()) {
        for (const auto& item : j) {
            print_json(item, indent + 4);
        }
    } else if (j.is_string()) {
        std::cout << j.get<str>() << std::endl;
    } else if (j.is_number_integer()) {
        std::cout << j.get<int>() << std::endl;
    } else if (j.is_number_float()) {
        std::cout << j.get<double>() << std::endl;
    } else if (j.is_boolean()) {
        std::cout << (j.get<bool>() ? "true" : "false") << std::endl;
    } else if (j.is_null()) {
        std::cout << "null" << std::endl;
    }
}

json cli(const str& command, const str& subcommand, const str& path, const str& name, const str& version, const str& new_name, const str& new_version, const str& new_wd_name) {
    if (command == "ep") {
        return handle_ep_command(subcommand, path, name, version, new_name, new_version);
    } else if (command == "gi") {
        return handle_gi_command(subcommand);
    } else if (command == "wd") {
        return handle_wd_command(subcommand, path, new_wd_name);
    } else {
        json jsonData;
        std::cerr << "Unexpected input! Available commands: ep, gi, wd. You entered: " << command << std::endl;
        jsonData["error"] = "Invalid command";
        return jsonData;
    }
}

int main(int argc, const char** argv) {
    NerMCManager::Sender sender;

    argparse::ArgumentParser program("nmm");

    program.add_argument("command")
        .help("command to execute (ep, gi, wd)");

    program.add_argument("subcommand")
        .help("subcommand to execute (list, create, delete, rename, import)");

    program.add_argument("path")
        .help("path for create or import")
        .default_value("");

    program.add_argument("-t", "name-version", "new-name-version")
        .help("new name and version for rename")
        .default_value("");

    program.add_argument("-name", "wd-name")
        .help("wd name for import")
        .default_value("");

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    str command = program.get<str>("command");
    str subcommand = program.get<str>("subcommand");
    str path = program.get<str>("path");
    str name_version = program.get<str>("name-version");
    str new_name_version = program.get<str>("new-name-version");
    str new_wd_name = program.get<str>("wd-name");
    
    str name = "";
    str version = "";
    str new_name = "";
    str new_version = "";

    splitByHyphen(name_version, name, version);
    splitByHyphen(new_name_version, new_name, new_version);

    json request_content = cli(command, subcommand, path, name, version, new_name, new_version, new_wd_name);

    json response = sender.request(request_content);

    print_json(response);

    return 0;
}