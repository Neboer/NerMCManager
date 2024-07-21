#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <zmq.hpp>
#include <nlohmann/json.hpp>
#include <functional>

using str = std::string;
using json = nlohmann::json;

namespace NerMCManager
{
    using JsonHandler = std::function<json(const json &req_data)>;

    class Server
    {
        public:
        Server(const str &address);
        void run();        
        void register_json_handlers(JsonHandler handler);
    
        private:
        zmq::context_t context;
        zmq::socket_t socket;
    
        JsonHandler request_handler;
    };
}
