#include <iostream>
#include <filesystem>
#include <fstream>
#include "sender.h"
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

void splitByColon(const std::string& input, std::string& left, std::string& right) {
    size_t colonPos = input.find(':');
    if (colonPos != std::string::npos) {
        left = input.substr(0, colonPos);
        right = input.substr(colonPos + 1);
    } else {
        std::cerr << "No colon found in the input string." << std::endl;
    }
}

nlohmann::json cli(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4, const std::string& tag, const std::string& version, const std::string& new_tag, const std::string& new_version) {
    nlohmann::json jsonData;

    try {
        if (p1 == "ep") {
            if (p2 == "list")
            {
            jsonData["type"] = "get_env_packs";
            }
            else if (p2 == "create")
            {
            jsonData["type"] = "create_env_pack";
            jsonData["args"]["new_ep_dir"] = p3;
            }
            else if (p2 == "delete")
            {
            jsonData["type"] = "delete_env_pack";
            jsonData["args"]["ep_name"] = tag;
            jsonData["args"]["ep_version"] = version;
            }
            else if (p2 == "rename")
            {
            jsonData["type"] = "rename_env_pack";
            jsonData["args"]["ep_name"] = tag;
            jsonData["args"]["ep_version"] = version;
            jsonData["args"]["new_ep_name"] = new_tag;
            jsonData["args"]["new_ep_version"] = new_version;
            }
            
            std::cout << "Now the JSON is..." << jsonData.dump(4) << std::endl;
        } 
        else if (p1 == "gi"){
            
        }
        else if (p1 == "wd")
        {

        }
        else if (p1 == "pt")
        {

        }
        
        
        else {
            std::cout << "Unexpected input! Available: ep. You: " << p1 << std::endl;
            jsonData["error"] = "Invalid command";
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
    std::string p3 = (argc > 3) ? argv[3] : "";
    std::string p4 = (argc > 4) ? argv[4] : "";
    std::string p5 = (argc > 5) ? argv[5] : "";
    std::string tag = "";
    std::string version = "";
    std::string new_tag = "";
    std::string new_version = "";
    splitByColon(p4, tag, version);
    splitByColon(p5, new_tag, new_version);
    nlohmann::json request_content = cli(p1, p2, p3, p4, tag, version, new_tag, new_version);

    // Send the request and receive the response
    nlohmann::json response = sender.request(request_content);

    // Print the response or use it as needed
    std::cout << "Response received: " << response.dump(4) << std::endl;

    return 0;
}
