#include <iostream>
#include "sender.h"  // Include the header file where Sender class is declared

int main() {
    // Create an instance of the Sender class
    NerMCManager::Sender sender;

    // Prompt the user to enter JSON request content
    std::cout << "Enter JSON request content:" << std::endl;
    json request_content;
    std::cin >> request_content;

    // Send the request and receive the response
    json response = sender.request(request_content);

    // Print the response or use it as needed
    std::cout << "Response received: " << response.dump() << std::endl;

    return 0;
}
