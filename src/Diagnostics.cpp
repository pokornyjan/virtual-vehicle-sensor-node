#include "Diagnostics.hpp"
#include <iostream>
#include <algorithm>

Diagnostics::Diagnostics() : initialized(false) {}

Diagnostics::~Diagnostics() {
    if (initialized) {
        clearMessages();
    }
}

void Diagnostics::initialize() {
    if (!initialized) {
        std::cout << "Diagnostics: Initializing..." << std::endl;
        initialized = true;
    }
}

void Diagnostics::logMessage(DiagnosticLevel level, const std::string& message, 
                           const std::string& component) {
    if (!initialized) {
        initialize();
    }
    
    DiagnosticMessage diagMsg{
        level,
        message,
        std::chrono::system_clock::now(),
        component
    };
    
    messages.push_back(diagMsg);
    
    // Also log to console
    std::string levelStr;
    switch (level) {
        case DiagnosticLevel::INFO: levelStr = "INFO"; break;
        case DiagnosticLevel::WARNING: levelStr = "WARNING"; break;
        case DiagnosticLevel::ERROR: levelStr = "ERROR"; break;
        case DiagnosticLevel::CRITICAL: levelStr = "CRITICAL"; break;
    }
    
    std::cout << "Diagnostics [" << levelStr << "] " << component 
              << ": " << message << std::endl;
}

const std::vector<DiagnosticMessage>& Diagnostics::getMessages() const {
    return messages;
}

void Diagnostics::clearMessages() {
    messages.clear();
    std::cout << "Diagnostics: Messages cleared" << std::endl;
}

bool Diagnostics::hasErrors() const {
    return std::any_of(messages.begin(), messages.end(), [](const auto& msg) {
        return msg.level == DiagnosticLevel::ERROR || msg.level == DiagnosticLevel::CRITICAL;
    });
}