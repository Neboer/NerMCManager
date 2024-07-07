#include "sender.h"
namespace NerMCManager
{
    Sender::Sender(): context(1) {
        client = zmq::socket_t(context, zmq::socket_type::req);
        client.connect("tcp://localhost:6223");
    }

    json Sender::request(const json &request_content)
    {
        zmq::message_t request(request_content.dump());
        client.send(request, zmq::send_flags::none);

        zmq::message_t response;
        client.recv(response, zmq::recv_flags::none);

        return json::parse(response.to_string());
    }
}