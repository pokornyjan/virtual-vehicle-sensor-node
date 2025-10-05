#include "../include/SensorManager.hpp"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "Running sensor tests..." << std::endl;
    
    try {
        // Test SensorManager
        SensorManager sensorManager;
        sensorManager.initialize();
        
        // Test adding sensors
        sensorManager.addSensor("temperature_01");
        sensorManager.addSensor("pressure_01");
        
        assert(sensorManager.isSensorActive("temperature_01"));
        assert(sensorManager.isSensorActive("pressure_01"));
        assert(!sensorManager.isSensorActive("nonexistent"));
        
        // Test getting active sensors
        auto sensors = sensorManager.getActiveSensors();
        assert(sensors.size() == 2);
        
        // Test removing sensor
        sensorManager.removeSensor("temperature_01");
        assert(!sensorManager.isSensorActive("temperature_01"));
        assert(sensorManager.isSensorActive("pressure_01"));
        
        sensorManager.shutdown();
        
        std::cout << "All sensor tests passed!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}