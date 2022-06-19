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
#include "SW_Push.h"

SW_Push::SW_Push(const std::string & name) : Wire(name) {
}

void SW_Push::press(bool b) {
    connected = b;
    update();
}

void SW_Push::toggle() {
    press(true);
    press(false);
}
