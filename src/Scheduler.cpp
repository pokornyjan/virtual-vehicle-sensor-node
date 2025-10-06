#include "Scheduler.hpp"
#include <iostream>
#include <algorithm>
#include <thread>

Scheduler::Scheduler() : running(false), initialized(false), mNumber(0) {}

Scheduler::~Scheduler() {
    if (running) {
        stop();
    }
}

void Scheduler::initialize() {
    if (!initialized) {
        std::cout << "Scheduler: Initializing..." << std::endl;
        initialized = true;
    }
}

void Scheduler::shutdown() {
    if (initialized) {
        stop();
        tasks.clear();
        std::cout << "Scheduler: Shutting down..." << std::endl;
        initialized = false;
    }
}

void Scheduler::setNumber(int number) {
    mNumber = number;
}


std::string Scheduler::addTask(std::function<void()> callback, 
                              std::chrono::milliseconds interval, 
                              bool recurring) {
    if (!initialized) {
        initialize();
    }
    
    static int taskCounter = mNumber;
    std::string taskId = "task_" + std::to_string(++taskCounter);
    
    Task task{
        taskId,
        callback,
        interval,
        std::chrono::system_clock::now() + interval,
        recurring,
        true
    };
    
    tasks.push_back(task);
    std::cout << "Scheduler: Added task " << taskId << std::endl;
    
    return taskId;
}

void Scheduler::removeTask(const std::string& taskId) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                          [&taskId](const Task& task) { return task.id == taskId; });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Scheduler: Removed task " << taskId << std::endl;
    }
}

void Scheduler::run() {
    if (!initialized) {
        initialize();
    }
    
    running = true;
    std::cout << "Scheduler: Starting..." << std::endl;
    
    while (running) {
        executeReadyTasks();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Scheduler::stop() {
    running = false;
    std::cout << "Scheduler: Stopping..." << std::endl;
}

bool Scheduler::isRunning() const {
    return running;
}

void Scheduler::executeReadyTasks() {
    auto now = std::chrono::system_clock::now();
    
    for (auto& task : tasks) {
        if (task.active && now >= task.nextExecution) {
            try {
                task.callback();
                
                if (task.recurring) {
                    task.nextExecution = now + task.interval;
                } else {
                    task.active = false;
                }
            } catch (const std::exception& e) {
                std::cerr << "Scheduler: Error executing task " << task.id 
                         << ": " << e.what() << std::endl;
            }
        }
    }
    
    // Remove inactive non-recurring tasks
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                              [](const Task& task) { return !task.active; }),
               tasks.end());
}