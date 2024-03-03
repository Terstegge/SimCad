cmake_minimum_required(VERSION 3.16)

target_sources(SimCad PRIVATE
    Net.cpp
    Pin.cpp
    plotRealTime.cpp
    PowerSupply.cpp
    SimCadException.cpp
)

target_include_directories(SimCad PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
