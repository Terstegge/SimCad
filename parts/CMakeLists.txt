cmake_minimum_required(VERSION 3.16)

target_include_directories(SimCad PUBLIC
    Connector
    Diode
    pspice
    Transistor_BJT
)

target_sources(SimCad PRIVATE
    Device/C.cpp
    Device/R_POT.cpp
    Display_Character/_7SEGMENT_CC.cpp
    Memory_EEPROM/_28C16.cpp
    Memory_Flash/SST39SF040.cpp
    Memory_RAM/_74189.cpp
    Memory_RAM/SRAM_32kb_DIP28.cpp
    Switch/SW_DIP_x04.cpp
    Switch/SW_DIP_x08.cpp
    Switch/SW_Push.cpp
    Switch/SW_SPDT.cpp
    Switch/SW_SPST.cpp
)

