///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  A simulation package for digital circuits
//
//  (c) 2020  A. Terstegge
//
///////////////////////////////////////////////
//
#include "State.h"

bool isStrong(State s) {
    return !(s & 0x06);
}

bool isWeak(State s) {
    return (s & 0x2);
}

State toWeak(State s) {
    if (s == LOW)
        return PD;
    else if (s == HIGH)
        return PU;
    else
        return s;
}

bool toBool(State s) {
    return s & 0x01;
}

State toState(bool s) {
    return s ? HIGH : LOW;
}

// Output operator
ostream & operator << (ostream & os, const State & s)  {
    switch (s) {
        case LOW:  os << "L"; break;
        case HIGH: os << "H"; break;
        case PD:   os << "d"; break;
        case PU:   os << "u"; break;
        case NC:   os << "x"; break;
        default:   os << "?"; break;
    }
    return os;
}
