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
// Standard Zener Diode with 4.7V breakdown voltage
//
#ifndef _PARTS_DIODE_INCLUDE_DZ2S047X0L_H_
#define _PARTS_DIODE_INCLUDE_DZ2S047X0L_H_

#include "DIODE_ZENER.h"

class DZ2S047X0L : public DIODE_ZENER {
public:
    DZ2S047X0L(const string & name="") : DIODE_ZENER(name, 0.725, -4.7) { }
};

#endif // _PARTS_DIODE_INCLUDE_DZ2S047X0L_H_
