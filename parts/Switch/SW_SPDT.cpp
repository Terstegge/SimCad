/////////////////////////////////////////////////
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
/////////////////////////////////////////////////
//
#include "SW_SPDT.h"

SW_SPDT::SW_SPDT(const std::string & name)
: NAME(p), NAME(_r21, INF), NAME(_r23, INF) {
    p[2].connect_to(_r21.p[1]);
    p[2].connect_to(_r23.p[1]);
    p[1].connect_to(_r21.p[2]);
    p[3].connect_to(_r23.p[2]);
}

void SW_SPDT::set(int c) {
    switch(c) {
        case con21: {
            if (_r21.getR() == 0) {
                return;
            } else {
                _r23.setR(INF);
                _r21.setR(0.0);
            }
            break;
        }
        case con23:
            if (_r23.getR() == 0) {
                return;
            } else {
                _r21.setR(INF);
                _r23.setR(0.0);
            }
            break;
    }
}
