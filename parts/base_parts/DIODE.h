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
// Low-level implementation of a diode based on the
// shockley equation. The forward voltage at 10mA is
// a CTOR parameter.
//
#ifndef _PARTS_BASE_PARTS_DIODE_H_
#define _PARTS_BASE_PARTS_DIODE_H_

#include "TwoPole.h"
#include <cmath>

using namespace std;

class DIODE : public TwoPole {
public:

    Pin & A, & C;   // References for Anode and Cathode

    DIODE(const string & name, double forward_voltage) 
        : TwoPole(name), C(p[1]), A(p[2]) {
        Ut = 0.026; // thermal voltage;
        Is = 1e-9;  // reverse saturation current
        // Calculate n from forward voltage at 10mA
        n  = forward_voltage / (Ut * log(0.01/Is + 1));
    }
    
    double Ichar(double U) override {
        // Shockley equation
        return Is * (exp(U / (Ut * n)) - 1);
    }

    double Rchar(double U) override {
        if (U == 0) {
            return (Ut * n) / Is;
        } else {
            return U / Ichar(U);
        }
    }

protected:
    // Diode configuration
    double Ut;  // thermal voltage (approx. 0.025V)
    double Is;  // reverse saturation current (10e-6...10e-12A)
    double n;   // emission coefficient
};

#endif // _PARTS_BASE_PARTS_DIODE_H_
