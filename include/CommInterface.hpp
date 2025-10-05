#pragma once

#include <string>
#include <functional>

class CommInterface {
public:
    CommInterface();
    ~CommInterface();
    
    bool initialize(int port = 8080);
    void shutdown();
    bool sendMessage(const std::string& message);
    void setMessageHandler(std::function<void(const std::string&)> handler);
    bool isConnected() const;
    
private:
    bool connected;
    int port;
    std::function<void(const std::string&)> messageHandler;
};