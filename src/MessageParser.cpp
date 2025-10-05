#include "MessageParser.hpp"
#include <iostream>
#include <sstream>

MessageParser::MessageParser() : initialized(false) {}

MessageParser::~MessageParser() {}

void MessageParser::initialize() {
    if (!initialized) {
        std::cout << "MessageParser: Initializing..." << std::endl;
        
        // Initialize type mappings
        typeMapping["SENSOR"] = MessageType::SENSOR_DATA;
        typeMapping["CMD"] = MessageType::COMMAND;
        typeMapping["STATUS"] = MessageType::STATUS;
        typeMapping["ERROR"] = MessageType::ERROR;
        
        initialized = true;
    }
}

ParsedMessage MessageParser::parseMessage(const std::string& rawMessage) {
    if (!initialized) {
        initialize();
    }
    
    ParsedMessage result;
    result.isValid = false;
    
    if (rawMessage.empty()) {
        return result;
    }
    
    // Simple parsing logic - assumes format: "TYPE:PAYLOAD"
    size_t colonPos = rawMessage.find(':');
    if (colonPos != std::string::npos) {
        std::string typeStr = rawMessage.substr(0, colonPos);
        std::string payload = rawMessage.substr(colonPos + 1);
        
        auto it = typeMapping.find(typeStr);
        if (it != typeMapping.end()) {
            result.type = it->second;
            result.payload = payload;
            result.isValid = true;
        } else {
            result.type = MessageType::UNKNOWN;
            result.payload = rawMessage;
        }
    } else {
        result.type = MessageType::UNKNOWN;
        result.payload = rawMessage;
    }
    
    std::cout << "MessageParser: Parsed message type " << static_cast<int>(result.type) << std::endl;
    return result;
}

std::string MessageParser::serializeMessage(const ParsedMessage& message) {
    std::string typeStr = "UNKNOWN";
    
    for (const auto& pair : typeMapping) {
        if (pair.second == message.type) {
            typeStr = pair.first;
            break;
        }
    }
    
    return typeStr + ":" + message.payload;
}

bool MessageParser::validateMessage(const std::string& message) const {
    if (message.empty()) return false;
    if (message.length() > 1024) return false; // Max message size
    
    return true;
}