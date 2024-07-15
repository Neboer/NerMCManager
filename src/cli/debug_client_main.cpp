#include <iostream>
#include <filesystem>
#include <fstream>
#include "sender.h"
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

nlohmann::json cli(const std::string& p1, const std::string& p2) {
    nlohmann::json jsonData;

    try {
        if (p1 == "ep") {
            jsonData["type"] = "create_env_pack";
            jsonData["args"]["new_ep_dir"] = p2;
            std::cout << "Now the JSON is..." << jsonData.dump(4) << std::endl;

        } else {
            std::cout << "Unexpected input! Available: ep. You: " << p1 << std::endl;
            jsonData["error"] = "Invalid command"; // Return an error field
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return jsonData; // Return JSON object
}

int main(int argc, char* argv[]) {
    NerMCManager::Sender sender;

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <command> <argument>" << std::endl;
        return 1;
    }

    std::string p1 = argv[1];
    std::string p2 = argv[2];

    nlohmann::json request_content = cli(p1, p2); // Get the request content from cli

    // Send the request and receive the response
    nlohmann::json response = sender.request(request_content);

    // Print the response or use it as needed
    std::cout << "Response received: " << response.dump(4) << std::endl;

    return 0;
}