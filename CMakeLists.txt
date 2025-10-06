cmake_minimum_required(VERSION 3.16)
project(VirtualVehicleSensorNode
    VERSION 1.0.0
    DESCRIPTION "C++ application for managing virtual vehicle sensors"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compile options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/CommInterface.cpp
    src/DataProcessor.cpp
    src/Diagnostics.cpp
    src/MessageParser.cpp
    src/Scheduler.cpp
    src/SensorManager.cpp
)

# Header files
set(HEADERS
    include/CommInterface.hpp
    include/DataProcessor.hpp
    include/Diagnostics.hpp
    include/MessageParser.hpp
    include/Scheduler.hpp
    include/SensorManager.hpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Enable testing
enable_testing()

# Test executable
add_executable(test_sensors tests/test_sensors.cpp src/SensorManager.cpp)
target_include_directories(test_sensors PRIVATE include)

add_executable(test_comm tests/test_comm.cpp src/CommInterface.cpp)
target_include_directories(test_comm PRIVATE include)

# Add tests
add_test(NAME SensorTests COMMAND test_sensors)
add_test(NAME CommTests COMMAND test_comm)

# Install target
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")