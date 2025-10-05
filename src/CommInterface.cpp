#include "CommInterface.hpp"
#include <iostream>

CommInterface::CommInterface() : connected(false), port(0) {}

CommInterface::~CommInterface() {
    if (connected) {
        shutdown();
    }
}

bool CommInterface::initialize(int port) {
    this->port = port;
    std::cout << "CommInterface: Initializing on port " << port << std::endl;
    // Simulate connection
    connected = true;
    return connected;
}

void CommInterface::shutdown() {
    if (connected) {
        std::cout << "CommInterface: Shutting down..." << std::endl;
        connected = false;
    }
}

bool CommInterface::sendMessage(const std::string& message) const {
    if (!connected) {
        return false;
    }
    
    std::cout << "CommInterface: Sending message: " << message << std::endl;
    return true;
}

void CommInterface::setMessageHandler(std::function<void(const std::string&)> handler) {
    messageHandler = handler;
}

bool CommInterface::isConnected() const {
    return connected;
}