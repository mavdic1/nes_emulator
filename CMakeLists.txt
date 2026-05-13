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
        src/Instructions/Store.cpp
        src/Instructions/Logic.cpp
        src/Instructions/Compare.cpp
        src/Instructions/Jump.cpp
        include/Bus.h
        src/Bus.cpp
        src/Instructions/Branch.cpp
        src/Instructions/IncDec.cpp
        src/Instructions/StatusFlag.cpp
        src/Instructions/System.cpp
        src/Instructions/Bitwise.cpp
        src/Instructions/Arithmetic.cpp)
