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
// This file contains all SimCad exception classes.
//
#ifndef _INCLUDE_SIMACADEXCEPTION_H_
#define _INCLUDE_SIMACADEXCEPTION_H_

#include "Net.h"
#include "Pin.h"
#include <stdexcept>
#include <iostream>
#include <string>

// Base class exception
class SimCadException {
public:
    virtual ~SimCadException() { }
    virtual std::ostream & toString(std::ostream & os) const = 0;
    friend std::ostream & operator << (std::ostream & os, const SimCadException & rhs);
};

// Short-circuit exception
//
// Thrown when there are multiple Pins driving a voltage source
// with different voltages within the same Net.
class shortCircuitException : public SimCadException {
public:
    shortCircuitException(Net * n) : _net(n) { }
    std::ostream & toString(std::ostream & os) const override;
private:
    Net * _net;
};

// Update-in-use exception
//
// Thrown when an update function is attached to a Pin,
// but the Pin already has an update function.
class updateInUseException : public SimCadException {
public:
    updateInUseException(Pin * p) : _pin(p) { }
    std::ostream & toString(std::ostream & os) const override;
private:
    Pin * _pin;
};

#endif // _INCLUDE_SIMACADEXCEPTION_H_
