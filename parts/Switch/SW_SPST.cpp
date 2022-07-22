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
// Low-level implementation of a simple switch.
// When on, both input states are propagated
// to the respective 'other' side.
//
#include "SW_SPST.h"

SW_SPST::SW_SPST(const std::string & name) : R(name, INF) {
}

void SW_SPST::setOn(bool b) {
    setR(b ? 0 : INF);
}

void SW_SPST::toggle() {
    setOn(true);
    setOn(false);
}
