#include <iostream>
#include "SensorManager.hpp"
#include "CommInterface.hpp"
#include "DataProcessor.hpp"
#include "Diagnostics.hpp"
#include "MessageParser.hpp"
#include "Scheduler.hpp"

int main() {
    std::cout << "Virtual Vehicle Sensor Node starting..." << std::endl;
    
    try {
        // Initialize core components
        SensorManager sensorManager;
        CommInterface commInterface;
        DataProcessor dataProcessor;
        Diagnostics diagnostics;
        MessageParser messageParser;
        Scheduler scheduler;
        
        std::cout << "All components initialized successfully!" << std::endl;
        std::cout << "Virtual Vehicle Sensor Node is running..." << std::endl;
        
        // Main application loop would go here
        // For now, just demonstrate that everything compiles
        
        std::cout << "Virtual Vehicle Sensor Node shutting down..." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}