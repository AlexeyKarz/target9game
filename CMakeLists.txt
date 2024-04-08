cmake_minimum_required(VERSION 3.27)
project(target9)

set(CMAKE_CXX_STANDARD 17)

add_executable(target9 main.cpp
        ClassesStack.h
        AutoWin.h
        GameState.cpp
        AutoWin.cpp
        ClassesStack.cpp
        GameFunctions.h
        GameFunctions.cpp
)
