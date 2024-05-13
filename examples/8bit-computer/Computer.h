/////////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
/////////////////////////////////////////////////
//
// This class is only a small wrapper around the generated
// class _8_bit_computer. Main purpose is easier use of the
// generated class by defining some names for LEDs and buttons
// as well as providing an ostream operator.
//
#ifndef _EXAMPLES_8_BIT_COMPUTER_H_
#define _EXAMPLES_8_BIT_COMPUTER_H_

#include "_8bit_computer.h"

enum { CLK_MODE_RUN      = SW_SPDT::con21, CLK_MODE_STEP   = SW_SPDT::con23 };
enum { PROG_MODE_ON      = SW_SPDT::con21, PROG_MODE_OFF   = SW_SPDT::con23 };
enum { OUT_MODE_UNSIGNED = SW_SPDT::con21, OUT_MODE_SIGNED = SW_SPDT::con23 };

class Computer : public _8bit_computer {
public:
    Computer(std::string name );
    virtual ~Computer() { }

    // Alias names for the control elements
    SW_Push    & STEP;
    SW_SPDT    & CLK_MODE;
    SW_Push    & STORE;
    SW_DIP_x08 & DATA;
    SW_SPDT    & PRGM_MODE;
    SW_DIP_x04 & ADDR;
    SW_SPDT    & OUT_MODE;
    SW_Push    & RESET;

    // Alias names for single LEDs and LED busses
    LEDRef BUS;
    LEDRef   A;
    LEDRef   B;
    LEDRef  IR;
    LED &   CF;
    LED &   ZF;
    LEDRef ALU;
    LEDRef RAM;
    LEDRef MAR;
    LEDRef PC;
    LEDRef MS;
    LEDRef CTRL;

    // The 3-digit Display. Values are set in main.cpp
    char Display[5] = { ' ', ' ', ' ', ' ', 0 };

    friend ostream & operator <<(ostream & os, const Computer & c);
};

#endif // _EXAMPLES_8_BIT_COMPUTER_H_
