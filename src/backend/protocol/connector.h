#pragma once
#include "../backend.h"

namespace NerMCManager
{
    using JsonHandler = std::function<json(const json &req_data)>;

    class Connector
    {
        public:
        Backend backend;
        json process_packet(const json &req_data);

        private:
        json execute_packet(const json &req_data);

    };

}