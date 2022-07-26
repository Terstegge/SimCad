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
#ifndef _PARTS_BASE_PARTS_DIODE_ZENER_H_
#define _PARTS_BASE_PARTS_DIODE_ZENER_H_

#include "TwoPole.h"
#include <cmath>

using namespace std;

class DIODE_ZENER : public TwoPole {
public:

    Pin & A, & C;   // References for Anode and Cathode

    DIODE_ZENER(const string & name, double forward_voltage, double breakdown_voltage)
        : TwoPole(name), C(p[1]), A(p[2]) {
        Ut = 0.026;                 // thermal voltage;
        Is = 1e-9;                  // reverse saturation current
        // Calculate n from forward voltage at 10mA
        nf  = forward_voltage / (Ut * log(0.01/Is + 1));
        Ub  = breakdown_voltage;    // breakdown voltage
        Ib  = 0.1;                  // breakdown current
        nb  = 0.5;                  // breakdown emission/stretch coefficient
    }
    
    double Ichar(double U) override {
        // Shockley equation + breakdown characteristic
        return Is * (exp(  U      / Ut / nf) - 1)
              -Ib * (exp((-U+Ub)  / Ut / nb) );
    }

    double Rchar(double U) override {
        if (U == 0) {
            return Ut * nf / Is;
        } else {
            return U / Ichar(U);
        }
    }

protected:
    // Forward configuration
    double Ut;  // thermal voltage (approx. 0.025V)
    double Is;  // reverse saturation current (10e-6...10e-12A)
    double nf;  // forward emission coefficient
    // Breakdown configuration
    double Ub;  // breakdown voltage
    double Ib;  // breakdown current
    double nb;  // breakdown emission coefficient
};

#endif // _PARTS_BASE_PARTS_DIODE_H_
