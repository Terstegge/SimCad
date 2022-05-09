/*
 * progdisplay.h
 *
 *  Created on: 08.05.2022
 *      Author: andreas
 */

#ifndef _PROG_DISPLAY_H_
#define _PROG_DISPLAY_H_

#include "stdint.h"

/**
 * This is a modified version of the Arduino sketch for programming
 * the EEPROM used in the 8-bit decimal display decoder described
 * in https://youtu.be/dLh1n2dErzE
 */

class prog_display {
private:
	uint8_t *_eeprom;

public:
	prog_display(uint8_t * eeprom);

	/*
	 *  Read a byte from the EEPROM at the specified address.
	 */
	uint8_t readEEPROM(int address);

	/*
	 *  Write a byte to the EEPROM at the specified address.
	 */
	void writeEEPROM(int address, uint8_t data);

	/*
	 * Program the display EEPROM
	 */
	void programEEPROM();

};

#endif // _PROG_DISPLAY_H_
