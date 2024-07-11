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
                // 处理接收消息失败的情况，例如记录日志或者抛出异常
                throw std::runtime_error("Failed to receive message: " + std::string(zmq_strerror(zmq_errno())));
            }

            return json::parse(static_cast<const char*>(response.data()), static_cast<const char*>(response.data()) + response.size());
        }
        catch (const std::exception &e)
        {
            // Handle any exceptions during send/receive
            return {{"error", e.what()}};
        }
    }
}
