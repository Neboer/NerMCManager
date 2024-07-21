#include <iostream>
#include <nlohmann/json.hpp>
#include "server/server.h"
#include "protocol/connector.h"
#include "backend.h"

using json = nlohmann::json;

int main()
{
    try
    {
        NerMCManager::BackendConfig config{};
        NerMCManager::Server server{"tcp://*:6223"};
        NerMCManager::Connector connector{
            NerMCManager::Backend{config}};
        server.register_json_handlers([&connector](const json& request) {
            return connector.process_packet(request);
        });
        server.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}