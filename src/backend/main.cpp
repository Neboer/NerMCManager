#include <iostream>
#include <nlohmann/json.hpp>
#include "server/server.h"

using json = nlohmann::json;

int main()
{
    NerMCManager::Server server{"tcp://*:6223"};
    server.run();

    return 0;
}