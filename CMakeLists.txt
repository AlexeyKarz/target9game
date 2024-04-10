cmake_minimum_required(VERSION 3.14)  # Minimum version of CMake required
project(target9game)  # Name of the project

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)  # source files
add_subdirectory(tests)  # test files
