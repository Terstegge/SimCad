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
//  (c) 2022  A. Terstegge
//
///////////////////////////////////////////////
//
// Low-level implementation of a diode based
// on the shockley equation. The forward 
// voltage at 10mA is a CTOR parameter.
//
#ifndef _INCLUDE_DIODE_H_
#define _INCLUDE_DIODE_H_

#include "TwoPole.h"
#include <cmath>

using namespace std;

class DIODE : public TwoPole {
public:

    Pin & A, & C;   // References for Anode and Cathode

    DIODE(const string & name, double forward_voltage) 
        : TwoPole(name), C(p[1]), A(p[2]) {
        // Saturation current
        Is = 1e-9;
        // Calculate Ut from forward voltage at 10mA
        Ut = forward_voltage / log(0.01/Is + 1);
    }
    
    double Ichar(double U) override {
        // Shockley equation
        return Is * (exp(U / Ut) -1);
    }

private:
    // Diode configuration
    double Ut;  // 0.025V * [1...2]
    double Is;  // 10e-6...10e-12
};

#endif // _INCLUDE_DIODE_H_
