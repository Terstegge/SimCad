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

SW_Push::SW_Push(const std::string & name) : R(name, INF) {
}

void SW_Push::press(bool b) {
    setR(b ? 0 : INF);
}

void SW_Push::toggle() {
    press(true);
    press(false);
}
