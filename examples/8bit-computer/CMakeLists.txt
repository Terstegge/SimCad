cmake_minimum_required(VERSION 3.12)

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

