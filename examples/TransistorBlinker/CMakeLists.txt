cmake_minimum_required(VERSION 3.12)

project(TransistorBlinker C CXX ASM)

add_subdirectory(../.. SimCad)

add_executable(TransistorBlinker
    main.cpp
)

net2cpp(TransistorBlinker TransistorBlinker.net)

# pull in needed libraries
target_link_libraries(TransistorBlinker 
    SimCad
    boost_iostreams
    boost_filesystem 
    pthread
)

