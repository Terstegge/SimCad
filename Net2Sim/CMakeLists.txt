cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(Net2Sim CXX)

add_executable(Net2Sim
    Net2Sim_main.cpp
    Net2Sim.cpp
    NetParser.cpp
    Node.cpp
)

