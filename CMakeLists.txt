cmake_minimum_required(VERSION 3.27)
project(target9)

set(CMAKE_CXX_STANDARD 17)

add_executable(target9 main.cpp
        ClassesStack/ClassesStack.h
        AutoWin/AutoWin.h
        AutoWin/GameStateStructure.cpp
        AutoWin/AutoWin.cpp
        ClassesStack/ClassesStack.cpp
        GameFunctions/GameFunctions.h
        GameFunctions/GameFunctions.cpp
)
