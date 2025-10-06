#include "DataProcessor.hpp"
#include <iostream>
#include <limits>

DataProcessor::DataProcessor() : initialized(false) {}

DataProcessor::~DataProcessor() {
    if (initialized) {
        clearData();
    }
}

void DataProcessor::initialize() {
    if (!initialized) {
        std::cout << "DataProcessor: Initializing..." << std::endl;
        // Set some default thresholds
        thresholds["temperature"] = 100.0;
        thresholds["pressure"] = 1000.0;
        thresholds["speed"] = 200.0;
        initialized = true;
    }
}

void DataProcessor::processSensorData(const SensorData& data) {
    if (!initialized) {
        initialize();
    }
    
    if (validateData(data)) {
        processedData.push_back(data);
        std::cout << "DataProcessor: Processed data from " << data.sensorId 
                  << " = " << data.value << " " << data.unit << std::endl;
    } else {
        std::cout << "DataProcessor: Invalid data from " << data.sensorId << std::endl;
    }
}

const std::vector<SensorData>& DataProcessor::getProcessedData() const {
    return processedData;
}

void DataProcessor::clearData() {
    processedData.clear();
    std::cout << "DataProcessor: Data cleared" << std::endl;
}

std::string DataProcessor::extractSensorType(const std::string& sensorId) const {
    // Assuming sensorId format is "type_id", e.g., "temperature_01"
    size_t underscorePos = sensorId.find('_');
    if (underscorePos != std::string::npos) {
        return sensorId.substr(0, underscorePos);
    }
    return sensorId; // If no underscore, return the whole ID
}

bool DataProcessor::validateData(const SensorData& data) const {
    // Basic validation
    if (data.sensorId.empty()) return false;
    if (data.value == std::numeric_limits<double>::infinity()) return false;
    if (data.value != data.value) return false; // Check for NaN
    
    // Extract sensor type from sensorId
    std::string sensorType = extractSensorType(data.sensorId);
    
    // Check against thresholds if available
    auto it = thresholds.find(sensorType);
    if (it != thresholds.end()) {
        return std::abs(data.value) <= it->second;
    }
    
    return true;
}