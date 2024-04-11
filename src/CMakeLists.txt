cmake_minimum_required(VERSION 3.27)
project(target9)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(/Users/alexeyks/CLionProjects/datastruct/target9/spdlog
        /Users/alexeyks/CLionProjects/datastruct/target9/spdlog/build)


add_executable(target9 main.cpp
        ClassesStack/ClassesStack.h
        AutoWin/AutoWin.h
        AutoWin/AutoWin.cpp
        ClassesStack/ClassesStack.cpp
        GameFunctions/GameFunctions.h
        GameFunctions/GameFunctions.cpp
        game_logic.cpp
        AutoWin/GameStateStruct.cpp
        AutoWin/GameStateStruct.h
)

target_link_libraries(target9 spdlog::spdlog)
