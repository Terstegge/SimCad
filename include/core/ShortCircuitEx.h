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
    short_circuit_exception(Net *n)
        : runtime_error("** Short Circuit Exception **"), _net(n) {
    }
    friend ostream & operator << (ostream & os, const short_circuit_exception & rhs) {
        os << "** Short Circuit Exception in Net " << rhs._net->getName() << " **"   << std::endl;
        if (rhs._net) os << rhs._net << std::endl;
        return os;
    }
private:
    Net * _net;

};

#endif // _SHORT_CIRCUIT_EXCEPTION_H_
