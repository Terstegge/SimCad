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

