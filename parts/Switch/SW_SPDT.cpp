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
#include "SW_SPDT.h"

SW_SPDT::SW_SPDT(const std::string & name)
: NAME(p), NAME(_wire21), NAME(_wire23) {
    p[2].connect_to(_wire21.p[1]);
    p[2].connect_to(_wire23.p[1]);
    p[1].connect_to(_wire21.p[2]);
    p[3].connect_to(_wire23.p[2]);
}

void SW_SPDT::set(int c) {
    switch(c) {
        case con21: {
            if (_wire21.connected) {
                return;
            } else {
                _wire23.connected = false;
                _wire21.connected = true;;
                _wire21.update();
                _wire23.update();
            }
            break;
        }
        case con23:
            if (_wire23.connected) {
                return;
            } else {
                _wire21.connected = false;
                _wire23.connected = true;;
                _wire21.update();
                _wire23.update();
            }
            break;
    }
}
