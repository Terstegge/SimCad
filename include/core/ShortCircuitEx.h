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
//#include "State.h"

#ifndef SHORT_CIRCUIT_EXCEPTION_H_
#define SHORT_CIRCUIT_EXCEPTION_H_

class short_circuit_exception : public std::runtime_error {
public:

    short_circuit_exception(Pin *p1, Pin *p2)
        : runtime_error("** Short Circuit Exception **"), _p1(p1), _p2(p2) {
    }

    friend ostream & operator << (ostream & os, const short_circuit_exception & rhs) {
        os << "** Short Circuit Exception in Net " << rhs._p1->getNetPtr()->getName() << " **"   << std::endl;
        if (rhs._p1) os << rhs._p1->getName() << " driving " << *rhs._p1 << std::endl;
        if (rhs._p2) os << rhs._p2->getName() << " driving " << *rhs._p2 << std::endl;
        return os;
    }

private:
    Pin * _p1;
    Pin * _p2;
};

#endif // _SHORT_CIRCUIT_EXCEPTION_H_
