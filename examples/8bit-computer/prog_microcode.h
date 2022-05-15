//
// This code is a modified version of the original Arduino sketch,
// which is specifically for programming the EEPROM used in the 8-bit
// decimal display decoder described in https://youtu.be/dLh1n2dErzE
//
#ifndef _PROG_MICROCODE_H_
#define _PROG_MICROCODE_H_

#include <cstdint>

class prog_microcode {

private:
    uint8_t *_eeprom_h;
    uint8_t *_eeprom_l;

public:
    prog_microcode(uint8_t *eeprom_h, uint8_t *eeprom_l);

    // Read a byte from the EEPROM at the specified address.
    uint8_t readEEPROM(int address);

    //Write a byte to the EEPROM at the specified address.
    void writeEEPROM(int address, uint8_t data);

    // Program the display EEPROM
    void programEEPROMs();

};

#endif // _PROG_MICROCODE_H_
