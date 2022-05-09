/*
 * SW_DIP_x08.cpp
 *
 *  Created on: 07.05.2022
 *      Author: andreas
 */

#include "SW_DIP_x08.h"

SW_DIP_x08::SW_DIP_x08(std::string name) : SW_DIP_x08_skel(name) {
}

void SW_DIP_x08::openSwitchesAt(int v) {
	this->SW1.setOn(!(v & 0x01));
	this->SW2.setOn(!(v & 0x02));
	this->SW3.setOn(!(v & 0x04));
	this->SW4.setOn(!(v & 0x08));
	this->SW5.setOn(!(v & 0x10));
	this->SW6.setOn(!(v & 0x20));
	this->SW7.setOn(!(v & 0x40));
	this->SW8.setOn(!(v & 0x80));
}

void SW_DIP_x08::closeSwitchesAt(int v) {
	this->SW1.setOn(v & 0x01);
	this->SW2.setOn(v & 0x02);
	this->SW3.setOn(v & 0x04);
	this->SW4.setOn(v & 0x08);
	this->SW5.setOn(v & 0x10);
	this->SW6.setOn(v & 0x20);
	this->SW7.setOn(v & 0x40);
	this->SW8.setOn(v & 0x80);
}
