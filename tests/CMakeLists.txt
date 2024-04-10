cmake_minimum_required(VERSION 3.10)
project(GameTests)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the Google Test subdirectory (assuming it is located within the 'tests' directory)
add_subdirectory(googletest)

# Include directories for Google Test header
include_directories(${gtest_SOURCE_DIR}/include)

# Assuming your source files (game_logic.cpp, etc.) are in the '../src' directory relative to 'tests'
include_directories(../src)

# Create a test executable target
# Make sure to include both the test file and the source file with your game logic
add_executable(game_test game_test.cpp
        ../src/game_logic.cpp
        ../src/AutoWin/AutoWin.cpp
        ../src/AutoWin/GameStateStruct.cpp
        ../src/ClassesStack/ClassesStack.cpp
        ../src/GameFunctions/GameFunctions.cpp)  # Add other source files as needed

# Link test executable against gtest & gtest_main
target_link_libraries(game_test gtest gtest_main)

# If your tests need pthread, link them as well
find_package(Threads REQUIRED)
target_link_libraries(game_test Threads::Threads)

# Enable testing functionalities
enable_testing()
add_test(NAME GameTest COMMAND game_test)
