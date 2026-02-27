cmake_minimum_required(VERSION 3.12)

project(SimpleNet1 C CXX ASM)

find_package(Boost REQUIRED iostreams)

add_subdirectory(../.. SimCad)

add_executable(Timer
        main.cpp
)

net2cpp(Timer Timer.net)

# pull in needed libraries
target_link_libraries(Timer
        SimCad
        pthread
        ${Boost_LIBRARIES}
)

