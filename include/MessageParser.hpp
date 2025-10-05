#pragma once

#include <string>
#include <map>
#include <vector>

enum class MessageType {
    SENSOR_DATA,
    COMMAND,
    STATUS,
    ERROR,
    UNKNOWN
};

struct ParsedMessage {
    MessageType type;
    std::string payload;
    std::map<std::string, std::string> headers;
    bool isValid;
};

class MessageParser {
public:
    MessageParser();
    ~MessageParser();
    
    void initialize();
    ParsedMessage parseMessage(const std::string& rawMessage);
    std::string serializeMessage(const ParsedMessage& message);
    bool validateMessage(const std::string& message) const;
    
private:
    std::map<std::string, MessageType> typeMapping;
    bool initialized;
};