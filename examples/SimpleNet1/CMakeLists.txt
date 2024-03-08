cmake_minimum_required(VERSION 3.12)

project(SimpleNet1 C CXX ASM)

add_subdirectory(../.. SimCad)

add_executable(SimpleNet1
    main.cpp
)

net2cpp(SimpleNet1 SimpleNet1.net)

# pull in needed libraries
target_link_libraries(SimpleNet1 SimCad pthread)

