#pragma once

#include <string>
#include <vector>
#include <chrono>

enum class DiagnosticLevel {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

struct DiagnosticMessage {
    DiagnosticLevel level;
    std::string message;
    std::chrono::system_clock::time_point timestamp;
    std::string component;
};

class Diagnostics {
public:
    Diagnostics();
    ~Diagnostics();
    
    void initialize();
    void logMessage(DiagnosticLevel level, const std::string& message, 
                   const std::string& component = "Unknown");
    const std::vector<DiagnosticMessage>& getMessages() const;
    void clearMessages();
    bool hasErrors() const;
    
private:
    std::vector<DiagnosticMessage> messages;
    bool initialized;
};