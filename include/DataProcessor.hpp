#pragma once

#include <string>
#include <vector>
#include <map>

struct SensorData {
    std::string sensorId;
    double value;
    long timestamp;
    std::string unit;
};

class DataProcessor {
public:
    DataProcessor();
    ~DataProcessor();
    
    void initialize();
    void processSensorData(const SensorData& data);
    const std::vector<SensorData>& getProcessedData() const;
    void clearData();
    bool validateData(const SensorData& data) const;
    
private:
    std::vector<SensorData> processedData;
    std::map<std::string, double> thresholds;
    bool initialized;
};