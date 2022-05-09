/*
 * SW_DIP_x08.cpp
 *
 *  Created on: 07.05.2022
 *      Author: andreas
 */

#include "SW_DIP_x04.h"

SW_DIP_x04::SW_DIP_x04(std::string name) : SW_DIP_x04_skel(name) {
}

void SW_DIP_x04::openSwitchesAt(int v) {
	this->SW1.setOn(!(v & 0x01));
	this->SW2.setOn(!(v & 0x02));
	this->SW3.setOn(!(v & 0x04));
	this->SW4.setOn(!(v & 0x08));
}

void SW_DIP_x04::closeSwitchesAt(int v) {
	this->SW1.setOn(v & 0x01);
	this->SW2.setOn(v & 0x02);
	this->SW3.setOn(v & 0x04);
	this->SW4.setOn(v & 0x08);
}

