#include "sender.h"

namespace NerMCManager
{
    Sender::Sender() : context(1), client(context, zmq::socket_type::req)
    {
        client.connect("tcp://localhost:6223");
    }

    json Sender::request(const json &request_content)
    {
        try
        {
            // Send request
            zmq::message_t request(request_content.dump());
            client.send(request, zmq::send_flags::none);

            // Receive response
            zmq::message_t response;
            std::optional<size_t> result = client.recv(response, zmq::recv_flags::none);

            if (!result.has_value())
            {
                throw std::runtime_error("Failed to receive message: " + std::string(zmq_strerror(zmq_errno())));
            }
            return json::parse(response.to_string());
        }
        catch (const std::exception &e)
        {
            // Handle any exceptions during send/receive
            return {{"error", e.what()}};
        }
    }
}
