#include "SensorManager.hpp"
#include <algorithm>
#include <iostream>

SensorManager::SensorManager() : initialized(false) {}

SensorManager::~SensorManager() {
    if (initialized) {
        shutdown();
    }
}

void SensorManager::initialize() {
    if (!initialized) {
        std::cout << "SensorManager: Initializing..." << std::endl;
        initialized = true;
    }
}

void SensorManager::shutdown() {
    if (initialized) {
        std::cout << "SensorManager: Shutting down..." << std::endl;
        activeSensors.clear();
        initialized = false;
    }
}

void SensorManager::addSensor(const std::string& sensorId) {
    if (std::find(activeSensors.begin(), activeSensors.end(), sensorId) == activeSensors.end()) {
        activeSensors.push_back(sensorId);
        std::cout << "SensorManager: Added sensor " << sensorId << std::endl;
    }
}

void SensorManager::removeSensor(const std::string& sensorId) {
    auto it = std::find(activeSensors.begin(), activeSensors.end(), sensorId);
    if (it != activeSensors.end()) {
        activeSensors.erase(it);
        std::cout << "SensorManager: Removed sensor " << sensorId << std::endl;
    }
}

bool SensorManager::isSensorActive(const std::string& sensorId) const {
    return std::find(activeSensors.begin(), activeSensors.end(), sensorId) != activeSensors.end();
}

const std::vector<std::string>& SensorManager::getActiveSensors() const {
    return activeSensors;
}