cmake_minimum_required(VERSION 3.12)

project(Tests C CXX ASM)

add_subdirectory(.. SimCad)
add_subdirectory(googletest)

set(test-dirs
    _74xx
    base_parts
    Memory_EEPROM
    Memory_RAM
)

foreach(test-dir ${test-dirs})
    file(GLOB_RECURSE cpp-files
        LIST_DIRECTORIES false
        RELATIVE ${CMAKE_CURRENT_LIST_DIR}
        "${test-dir}/*.cpp"
    )
    set(test-files "${test-files};${cpp-files}")
endforeach()

enable_testing()

add_executable(simcad-tests
    ${test-files}
)

target_include_directories(simcad-tests PRIVATE _74xx)

# pull in needed libraries
target_link_libraries(simcad-tests SimCad gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(simcad-tests)

