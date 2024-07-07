#include "connector.h"
#include <map>
#include <spdlog/spdlog.h>
#include <vector>

namespace NerMCManager
{
    json Connector::process_packet(const json &req_data)
    {
        try
        {
            json payload = execute_packet(req_data);
            return {{"payload", payload}};
        }
        catch (const std::exception &e)
        {
            spdlog::error("process_packet: Error while processing packet: {}", e.what());
            return {{"error", "Error while processing packet."}};
        }
    }

    json Connector::execute_packet(const json &req_data)
    {
        str command_type = req_data["type"];
        json arguments = req_data["args"];

        // ep commands
        // no-reply commands
        if (command_type == "create_env_pack")
        {
            spdlog::info("Creating env pack {}.", arguments["new_ep_dir"].dump());
            return backend.create_env_pack(arguments["new_ep_dir"]).to_json();
        }
        else if (command_type == "delete_env_pack")
        {
            spdlog::info("Deleting env pack {}.", arguments["ep_name"].dump() + "-" + arguments["ep_version"].dump());
            return backend.delete_env_pack(arguments["ep_name"], arguments["ep_version"]).to_json();
        }
        else if (command_type == "rename_env_pack")
        {
            spdlog::info("Renaming env pack {} to {}.", arguments["ep_name"].dump() + "-" + arguments["ep_version"].dump(), arguments["new_ep_name"].dump() + "-" + arguments["new_ep_version"].dump());
            return backend.rename_env_pack(arguments["ep_name"].dump(), arguments["ep_version"].dump(), arguments["new_ep_name"].dump(), arguments["new_ep_version"].dump()).to_json();
        }

        // reply commands
        else if (command_type == "get_env_packs")
        {
            std::vector<EnvPack> eps = backend.get_env_packs();
            json eps_json = json::array();
            for (EnvPack ep : eps)
            {
                eps_json.push_back(ep.to_json());
            }
            return eps_json;
        }

        else
            return {{"error", "Unknown command type."}};
    }
}