#include "gi_command.h"
#include <iostream>

json handle_gi_command(const str& subcommand) {
    json jsonData;

    if (subcommand == "list") {
        jsonData["type"] = "get_game_instance";
    } else {
        std::cerr << "Unexpected subcommand for gi: " << subcommand << std::endl;
        jsonData["error"] = "Invalid subcommand";
    }

    return jsonData;
}
