///////////////////////////////////////////////
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//  A simulation package for digital circuits
//  (c) 2020  A. Terstegge
///////////////////////////////////////////////
//
// Low-level implementation of a Si diode
// (forward voltage approx 0.7V)
//
#ifndef _INCLUDE_1N4148_H_
#define _INCLUDE_1N4148_H_

#include "TwoPole.h"
#include <iostream>
#include <cmath>

using namespace std;

class _1N4148 : public TwoPole {
public:
    Pin & A, & C;   // References for Anode and Cathode
    _1N4148(const string & name="") : TwoPole(name), C(p[1]), A(p[2]) {
        Ut = 0.035;
        Is = 1e-10;
    }
    double Ichar(double U) override {
        // Shockley equation
        return Is * (exp(U / Ut) -1);
    }

protected:
    // Diode configuration
    double Ut;  // 0.025V * [1...2]
    double Is;  // 10e-6...10e-12
};

#endif // INCLUDE_1N4148_H_
