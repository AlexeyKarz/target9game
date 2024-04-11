cmake_minimum_required(VERSION 3.14)  # Minimum version of CMake required
project(target9game)  # Name of the project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the location of the spdlog header files
#include_directories(${PROJECT_SOURCE_DIR}/spdlog)

# Add subdirectories
add_subdirectory(src)  # source files
add_subdirectory(tests)  # test files
