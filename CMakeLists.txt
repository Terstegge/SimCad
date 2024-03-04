#/////////////////////////////////////////////////
#//
#//  This file is part of
#//      ___  ____  __  __  ___    __    ____
#//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
#//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
#//     (___/(____)(_/\/\_)\___)(__)(__)(____/
#//
#//  A simulation library for electronic circuits
#//  See also https://github.com/Terstegge/SimCad
#//  (c) Andreas Terstegge
#//
#/////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.16)
include(.cmake-functions)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "-O3")

project(SimCad CXX)

add_subdirectory(Net2Sim)

add_library(SimCad)

file(GLOB_RECURSE netfiles
    LIST_DIRECTORIES false
    RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    "parts/*.net"
)
foreach(netfile ${netfiles})
    net2cpp(SimCad ${netfile})
endforeach()

add_subdirectory(src)
add_subdirectory(parts)
