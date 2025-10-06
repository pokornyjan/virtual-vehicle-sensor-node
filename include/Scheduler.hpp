#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <string>

struct Task {
    std::string id;
    std::function<void()> callback;
    std::chrono::milliseconds interval;
    std::chrono::system_clock::time_point nextExecution;
    bool recurring;
    bool active;
};

class Scheduler {
public:
    Scheduler();
    ~Scheduler();
    
    void initialize();
    void shutdown();
    void setNumber(int number);
    std::string addTask(std::function<void()> callback, 
                       std::chrono::milliseconds interval, 
                       bool recurring = true);
    void removeTask(const std::string& taskId);
    void run();
    void stop();
    bool isRunning() const;
    
private:
    std::vector<Task> tasks;
    bool running;
    bool initialized;
    int mNumber;
    void executeReadyTasks();
};