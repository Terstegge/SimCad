/*
 * This file is part of the DigiSim Software -
 * a simulation package for digital circuits.
 *
 * (c) 2020 A. Terstegge
 */

#include "State.h"

bool isStrong(State s) {
    return !(s & 0x06);
}

bool toBool(State s) {
    // LSB of State reflects the boolean state
    return s & 0x01;
}

State toState(bool s) {
    return s ? HIGH : LOW;
}

// Output operator
ostream & operator << (ostream & os, const State s) {
    switch (s) {
        case LOW:  os << "LOW";  break;
        case HIGH: os << "HIGH"; break;
        case PD:   os << "PD";   break;
        case PU:   os << "PU";   break;
        case NC:   os << "NC";   break;
    }
    return os;
}

ostream & operator <<= (ostream & os, const State s)  {
    switch (s) {
        case LOW:  os << "0"; break;
        case HIGH: os << "1"; break;
        case PD:   os << "d"; break;
        case PU:   os << "u"; break;
        case NC:   os << "x"; break;
    }
    return os;
}
