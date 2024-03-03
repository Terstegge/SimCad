cmake_minimum_required(VERSION 3.12)

project(R2R-Ladder C CXX ASM)

add_subdirectory(../.. SimCad)

add_executable(R2R-Ladder
    main.cpp
)

net2cpp(R2R-Ladder R2R-Ladder-DAC.net)

# pull in needed libraries
target_link_libraries(R2R-Ladder SimCad pthread)

