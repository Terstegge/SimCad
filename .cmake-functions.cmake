function(net2cpp TARGET NETFILE)
    # Parse argument
    # cmake_parse_arguments(png_to_cpp "" "BG_COLOR;OUTPUT_FILE" "" ${ARGN} )

    # Paramters are all relative to current CMakeList.txt
    get_filename_component(NAME_WE   ${NETFILE} NAME_WE)
    get_filename_component(DIRECTORY ${NETFILE} DIRECTORY)

    # Convert base name to C++-compatible class name
    string(REPLACE "-" "_" NAME_WE ${NAME_WE})
    string(REPLACE "(" "_" NAME_WE ${NAME_WE})
    string(REPLACE ")" "_" NAME_WE ${NAME_WE})
    string(REPLACE " " "_" NAME_WE ${NAME_WE})
    string(REGEX MATCH "^[0-9]" START_DIGIT ${NAME_WE})
    if (NOT "${START_DIGIT}" STREQUAL "")
        string(PREPEND NAME_WE "_")
    endif()

    # Set the file names
    set(NETFILE "${CMAKE_CURRENT_LIST_DIR}/${NETFILE}")
    set(CPPFILE "${CMAKE_CURRENT_LIST_DIR}/${DIRECTORY}/${NAME_WE}.cpp")
    set(HFILE   "${CMAKE_CURRENT_LIST_DIR}/${DIRECTORY}/${NAME_WE}.h")

    # Add a new target which depends on the cpp file
    set(NET_TARGET "${NAME_WE}_gen")
    add_custom_target(${NET_TARGET} DEPENDS ${CPPFILE} ${HFILE})
    add_custom_command(
        OUTPUT          ${CPPFILE} ${HFILE}
        MAIN_DEPENDENCY ${NETFILE}
        COMMAND Net2Sim ${NETFILE}
    )
    add_dependencies(${TARGET} ${NET_TARGET})

    # Update target
    target_sources(${TARGET}
        PRIVATE ${CPPFILE}
    )
    target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${DIRECTORY}
    )
endfunction()
