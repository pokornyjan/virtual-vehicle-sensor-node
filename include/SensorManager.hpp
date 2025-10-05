#pragma once

#include <vector>
#include <string>
#include <memory>

class SensorManager {
public:
    SensorManager();
    ~SensorManager();
    
    void initialize();
    void shutdown();
    void addSensor(const std::string& sensorId);
    void removeSensor(const std::string& sensorId);
    bool isSensorActive(const std::string& sensorId) const;
    std::vector<std::string> getActiveSensors() const;
    
private:
    std::vector<std::string> activeSensors;
    bool initialized;
};