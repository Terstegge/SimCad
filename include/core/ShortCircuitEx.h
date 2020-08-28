/*
 * This file is part of the DigiSim Software -
 * a simulation package for digital circuits.
 *
 * (c) 2020 A. Terstegge
 *
 * The short_circuit_exception is thrown when
 * a short circuit is detected. This means that
 * within one Net, two Pins are driving the Net
 * with different values (LOW/HIGH). The two Pins
 * which cause the short circuit are given as the
 * CTOR parameters.
 *
 */

#include <stdexcept>
#include <iostream>
using std::ostream;

#include "Pin.h"
#include "State.h"

#ifndef _SHORT_CIRCUIT_EXCEPTION_H_
#define _SHORT_CIRCUIT_EXCEPTION_H_

class short_circuit_exception : public std::runtime_error {
public:

    short_circuit_exception(State s1, State s2)
        : runtime_error("** Short Circuit Exception **"),
          _s1(s1), _s2(s2), _p1(nullptr), _p2(nullptr) {
    }

    void setPin1(Pin * p) { _p1 = p; }
    void setPin2(Pin * p) { _p2 = p; }

    friend ostream & operator << (ostream & os, const short_circuit_exception & rhs) {
        os << "** Short Circuit Exception **"   << std::endl;
        os << rhs._s1 << " versus " << rhs._s2 << std::endl;
        if (rhs._p1) os << rhs._p1->getName() << " driving " << rhs._p1->getDrvState() << std::endl;
        if (rhs._p2) os << rhs._p2->getName() << " driving " << rhs._p2->getDrvState() << std::endl;
        return os;
    }

private:
    State _s1;
    State _s2;
    Pin * _p1;
    Pin * _p2;
};

#endif // _SHORT_CIRCUIT_EXCEPTION_H_
