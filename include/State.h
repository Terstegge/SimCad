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
// The struct 'State' represents the electrical
// state of a Pin or Net. It is also used as
// the result type for EVS (Equivalent Voltage
// Source) computations.
// The class contains a voltage U and an ohmic
// conductance G.
//
#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

// Predefined States
struct State;
extern State LOW;
extern State HIGH;
extern State NC;

#include <cmath>    // fabs()
#include <limits>   // infinity
#include <iostream>

#define SUPPLY_VOLTAGE  5.0
#define EPSILON         1e-8
#define INF             std::numeric_limits<float>::infinity()

struct  State {
    // Attributes
    float   _U;
    float   _R;

    // Standard constructor
    // A default new state is always NC
    State(float u=0.0, float r=INF) : _U(u), _R(r) { }

    // Type conversion for booleans
    State(bool b) {
        _U  = b ? SUPPLY_VOLTAGE : 0.0;
        _R  = 0.0;
    }
    inline operator bool () const {
        if (*this == NC) {
             return true;
        } else {
            return ( _U > (SUPPLY_VOLTAGE/2) );
        }
    }

    // Comparison operators
    bool operator == (const State & rhs) const {
        if ((_U == rhs._U) && (_R== rhs._R)) {
            return true;
        } else {
            return (fabs(_U - rhs._U) < EPSILON) &&
                   (fabs(_R - rhs._R) < EPSILON);
        }
    }
    bool operator != (const State & rhs) const {
        return !(*this == rhs);
    }

    // Helper methods
    bool isStrong() {
        return (_R == 0.0);
    }

    // Stream output operator
    friend std::ostream & operator << (std::ostream & os, const State & s);
};

#endif // INCLUDE_STATE_H_
