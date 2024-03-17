cmake_minimum_required(VERSION 3.12)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "-O3")
set (CMAKE_CXX_FLAGS "-fno-var-tracking")

project(8bit-computer C CXX ASM)

add_subdirectory(../.. SimCad)

add_executable(Computer
    Computer.cpp
    main.cpp
    prog_display.cpp
    prog_microcode.cpp
)

net2cpp(Computer kicad/8bit-computer.net)

# pull in needed libraries
target_link_libraries(Computer SimCad pthread)

