#include "../include/CommInterface.hpp"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Running communication tests..." << std::endl;
    
    try {
        // Test CommInterface
        CommInterface commInterface;
        
        // Test initialization
        bool initialized = commInterface.initialize(8080);
        assert(initialized);
        assert(commInterface.isConnected());
        
        // Test message sending
        bool sent = commInterface.sendMessage("Hello, World!");
        assert(sent);
        
        // Test message handler
        bool handlerCalled = false;
        commInterface.setMessageHandler([&handlerCalled](const std::string& msg) {
            handlerCalled = true;
            std::cout << "Received message: " << msg << std::endl;
        });
        
        commInterface.shutdown();
        assert(!commInterface.isConnected());
        
        std::cout << "All communication tests passed!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}