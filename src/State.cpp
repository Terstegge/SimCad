/*
 * This file is part of the DigiSim Software -
 * a simulation package for digital circuits.
 *
 * (c) 2020 A. Terstegge
 */

#include "State.h"

bool toBool(State s) {
    return (s == LOW) ? false : true;
}

State toState(bool s) {
    return s ? HIGH : LOW;
}

// Output operator
ostream & operator << (ostream & os, const State s) {
    switch (s) {
        case LOW:  os << "LOW";  break;
        case HIGH: os << "HIGH"; break;
        case NC:   os << "NC";   break;
    }
    return os;
}

ostream & operator <<= (ostream & os, const State s)  {
    switch (s) {
        case LOW:  os << "0";  break;
        case HIGH: os << "1"; break;
        case NC:   os << "x";   break;
    }
    return os;
}
