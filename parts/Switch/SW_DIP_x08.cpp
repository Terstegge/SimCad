///////////////////////////////////////////////
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
///////////////////////////////////////////////
//
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
