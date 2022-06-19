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
// Class for a simple wire connection. The attribute
// 'connected' controls if the Wire is electrically
// connecting the two Pins p[1] and p[2] or not.
// A Wire is basically a resistor with only two
// possible value, 0 and INF.
//
#ifndef _INCLUDE_WIRE_H_
#define _INCLUDE_WIRE_H_

#include "TwoPole.h"

class Wire : public TwoPole {
public:
    bool connected;

    Wire(const std::string & name) : TwoPole(name), connected(false) {
    }

    double Rchar(double U) {
        return connected ? 0 : INF;
    }
};

#endif // _INCLUDE_WIRE_H_
