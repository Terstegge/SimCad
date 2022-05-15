/*
 * Computer.h
 *
 *  Created on: 14.05.2022
 *      Author: andreas
 */

#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "8bit-computer.h"

enum { CLK_MODE_RUN      = SW_SPDT::con21, CLK_MODE_STEP   = SW_SPDT::con23 };
enum { PROG_MODE_ON      = SW_SPDT::con21, PROG_MODE_OFF   = SW_SPDT::con23 };
enum { OUT_MODE_UNSIGNED = SW_SPDT::con21, OUT_MODE_SIGNED = SW_SPDT::con23 };

class Computer : public _8bit_computer {
public:
    Computer(std::string name );

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
    LEDRef PC;
    LEDRef MAR;
    LEDRef MS;
    LEDRef CTRL;

    friend ostream & operator <<(ostream & os, const Computer & c);
};

#endif // _COMPUTER_H_
