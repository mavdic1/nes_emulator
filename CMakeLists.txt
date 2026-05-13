cmake_minimum_required(VERSION 4.1)
project(nes)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(nes main.cpp
        src/CPU.cpp
        include/CPU.h
        include/Memory.h
        src/Memory.cpp
        include/Types.h
        src/Instructions/Instructions.h
        src/Instructions/Transfer.cpp
        src/Instructions/Stack.cpp
        src/Instructions/Instructions.cpp
        src/Instructions/Load.cpp
        src/Instructions/Store.cpp)
