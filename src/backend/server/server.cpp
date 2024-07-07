#include "server.h"
#include <spdlog/spdlog.h>

namespace NerMCManager
{

    Server::Server(const std::string &address)
        : context{1}, socket{context, zmq::socket_type::rep}
    {
        socket.bind(address);
    }

    void Server::register_json_handlers(JsonHandler handler)
    {
        request_handler = handler;
    }

    void Server::run()
    {
        spdlog::info("Server is running");
        for (;;)
        {
            try
            {
                zmq::message_t request;

                socket.recv(request, zmq::recv_flags::none);
                spdlog::info("Received: {}", request.to_string());

                json request_content = json::parse(request.to_string());
                spdlog::info("Parsed JSON: {}", request_content.dump());

                json reply_result = request_handler(request_content);
                socket.send(zmq::buffer(reply_result.dump()), zmq::send_flags::none);
                spdlog::info("Sent: {}", reply_result.dump());
            }
            catch (json::parse_error &e)
            {
                str error_reason = e.what();
                spdlog::error("Failed to parse JSON: {}", error_reason);
                json error_msg = {{"error", "Failed to parse JSON." + error_reason}};

                socket.send(zmq::buffer(error_msg.dump()), zmq::send_flags::none);
                continue;
            }
            catch (zmq::error_t &e)
            {
                spdlog::error("Failed on processing message: {}", e.what());
                throw e;
            }
        }
    }
}