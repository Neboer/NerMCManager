#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <zmq.hpp>
#include <nlohmann/json.hpp>

namespace NerMCManager
{
    class Server
    {
    public:
        Server(const std::string &address);
        void run();

    private:
        void handle_request(zmq::message_t &request);

        zmq::context_t context;
        zmq::socket_t socket;
    };

}
