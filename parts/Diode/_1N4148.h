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
// Standard Si-diode 1N4148 (forward voltage 0.725V at 10mA)
//
#ifndef _PARTS_DIODE_INCLUDE_1N4148_H_
#define _PARTS_DIODE_INCLUDE_1N4148_H_

#include "DIODE.h"

class _1N4148 : public DIODE {
public:
    _1N4148(const string & name="") : DIODE(name, 0.725) { }
};

#endif // _PARTS_DIODE_INCLUDE_1N4148_H_
