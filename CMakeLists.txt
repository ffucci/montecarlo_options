cmake_minimum_required(VERSION 3.10)

# set the project name
project(OptionsMontecarlo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions("-std=c++20")

# add the executable
add_executable(execute_simulation src/simulation.cpp)


