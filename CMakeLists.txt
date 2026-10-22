cmake_minimum_required(VERSION 3.15)
project(TuringMachine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(turing
    src/main.cpp
    src/Tape.cpp
    src/TuringMachine.cpp
    src/ConfigParser.cpp
)
target_include_directories(turing PRIVATE include)