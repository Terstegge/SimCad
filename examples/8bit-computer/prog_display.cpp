//
// This code is a modified version of the original Arduino sketch,
// which is specifically for programming the EEPROM used in the 8-bit
// decimal display decoder described in https://youtu.be/dLh1n2dErzE
//
#include "prog_display.h"

#include <iostream>
using namespace std;

prog_display::prog_display(uint8_t *eeprom) :
        _eeprom(eeprom) {
}

uint8_t prog_display::readEEPROM(int address) {
    return _eeprom[address];
}

void prog_display::writeEEPROM(int address, uint8_t data) {
    _eeprom[address] = data;
}

void prog_display::programEEPROM() {

    // Bit patterns for the digits 0..9
    //
    //      AAAAA
    //     F     B
    //     F     B
    //      GGGGG
    //     E     C
    //     E     C
    //      DDDDD   DP
    //
    //  Bit  |7|6|5|4|3|2|1|0|
    //  -----+-+-+-+-+-+-+-+-+
    //       DP A B C D E F G
    //
    //                    '0'   '1'   '2'   '3'   '4'   '5'   '6'   '7'   '8'   '9'
    uint8_t digits[] = { 0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b };

    cout << "Programming display EEPROM" << endl;

    // Unsigned digits
    for (int value = 0; value < 256; ++value) {
        writeEEPROM(value, digits[value % 10]);
    }
    for (int value = 0; value < 256; ++value) {
        writeEEPROM(value + 256, digits[(value / 10) % 10]);
    }
    for (int value = 0; value < 256; ++value) {
        writeEEPROM(value + 512, digits[(value / 100) % 10]);
    }
    for (int value = 0; value < 256; ++value) {
        writeEEPROM(value + 768, 0);
    }

    // Signed digits
    for (int value = -128; value < 128; ++value) {
        writeEEPROM((uint8_t) value + 1024, digits[abs(value) % 10]);
    }
    for (int value = -128; value < 128; ++value) {
        writeEEPROM((uint8_t) value + 1280, digits[abs(value / 10) % 10]);
    }
    for (int value = -128; value < 128; ++value) {
        writeEEPROM((uint8_t) value + 1536, digits[abs(value / 100) % 10]);
    }
    for (int value = -128; value < 128; ++value) {
        if (value < 0) {
            writeEEPROM((uint8_t) value + 1792, 0x01);
        } else {
            writeEEPROM((uint8_t) value + 1792, 0);
        }
    }
}
