cmake_minimum_required(VERSION 3.12)

project(SimpleNet2 C CXX ASM)

add_subdirectory(../.. SimCad)

add_executable(SimpleNet2
    main.cpp
)

net2cpp(SimpleNet2 SimpleNet2.net)

# pull in needed libraries
target_link_libraries(SimpleNet2 SimCad pthread)

