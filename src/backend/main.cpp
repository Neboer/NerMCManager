#include <iostream>
#include <nlohmann/json.hpp>
#include "server/server.h"
#include "protocol/connector.h"
#include "backend.h"

using json = nlohmann::json;

int main()
{
    NerMCManager::BackendConfig config{};
    NerMCManager::Server server{"tcp://*:6223"};
    NerMCManager::Connector connector{
        NerMCManager::Backend{config}};
    server.register_json_handlers([&connector](const json& request) {
        return connector.process_packet(request);
    });

    server.run();

    return 0;
}