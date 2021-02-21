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
// Low-level implementation of a diode, which
// is simulated with a variable resistance.
//
#ifndef _INCLUDE_1N4148_H_
#define _INCLUDE_1N4148_H_

#include "TwoPole.h"
#include "R.h"
#include <iostream>

using namespace std;

class _1N4148 : public TwoPole {
protected:
    //////////////////////
    // Diode configuration
    //////////////////////
    const float Us = 0.7;           // Forward voltage
    const float G1 = 1.0 / 100000;  // Resistance up to 0V and for free floating case
    const float G2 = 1.0 / 280;     // Resistance up to Us
    const float G3 = 1.0 / 1.0;     // Resistance from Us on

public:
    Pin & A, & C;   // References for Anode and Cathode
    
    _1N4148(const string & name="") : TwoPole(name), C(p[1]), A(p[2]) {
        // Set default resistance
        setG(G1);
    }

    void p1_callback() override { calculate(); }
    void p2_callback() override { calculate(); }

    void calculate() {
        // Calculate SVS parameters
        float Ul = A.Uw() - C.Uw();
        float Gi = 1.0 / (1.0/A.Gw() + 1.0/C.Gw());
        float Ik = Ul * Gi;
        // Reverse voltage case
        if (Ul < 0.0) { setG( G1 ); return; }
        // Calculate resulting voltage drop
        float u = (Ik + Us * (G3 - G2)) / (G3 + Gi);
        // Case up to Us
        if (u < Us) { setG( G2 ); return; }
        // Case from Us on
        setG( Gi * (Ul/u - 1) );
    }
};

#endif // INCLUDE_1N4148_H_
