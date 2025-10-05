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

std::vector<SensorData> DataProcessor::getProcessedData() const {
    return processedData;
}

void DataProcessor::clearData() {
    processedData.clear();
    std::cout << "DataProcessor: Data cleared" << std::endl;
}

bool DataProcessor::validateData(const SensorData& data) const {
    // Basic validation
    if (data.sensorId.empty()) return false;
    if (data.value == std::numeric_limits<double>::infinity()) return false;
    if (data.value != data.value) return false; // Check for NaN
    
    // Check against thresholds if available
    auto it = thresholds.find(data.sensorId);
    if (it != thresholds.end()) {
        return std::abs(data.value) <= it->second;
    }
    
    return true;
}