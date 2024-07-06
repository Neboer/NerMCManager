#include "server.h"

namespace NerMCManager
{

    Server::Server(const std::string &address)
        : context{1}, socket{context, zmq::socket_type::rep}
    {
        socket.bind(address);
    }

    void Server::run()
    {
        using namespace std::chrono_literals;
        const std::string response_data{"World"};

        for (;;)
        {
            zmq::message_t request;

            socket.recv(request, zmq::recv_flags::none);
            std::cout << "Received " << request.to_string() << std::endl;

            handle_request(request);

            socket.send(zmq::buffer(response_data), zmq::send_flags::none);
        }
    }

    void Server::handle_request(zmq::message_t &request)
    {
        try
        {
            nlohmann::json json_request = nlohmann::json::parse(request.to_string());
            std::cout << "Parsed JSON: " << json_request.dump(4) << std::endl;
        }
        catch (nlohmann::json::parse_error &e)
        {
            std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        }
    }
}