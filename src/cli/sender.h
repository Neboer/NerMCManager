#include <string>
#include <iostream>
#include <vector>

#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace NerMCManager
{

    class Sender
    {
    public:
        zmq::context_t context;
        zmq::socket_t client;

        Sender();
        json request(const json &request_content);
    };

}