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
    const double Us = 0.7;           // Forward voltage
    const double G1 = 1.0 / 100000;  // Resistance up to 0V and for free floating case
    const double G2 = 1.0 / 280;     // Resistance up to Us
    const double G3 = 1.0 / 1.0;     // Resistance from Us on

public:
    Pin & A, & C;   // References for Anode and Cathode
    
    _1N4148(const string & name="") : TwoPole(name), C(p[1]), A(p[2]) {
        // Set default resistance
        setG(G1);
    }

    void p1_callback() override { calculate(); }
    void p2_callback() override { calculate(); }

    void calculate() {
        double Ig = Us * G2;
        double I  = A.I();

        if (I < 0.0) { setG( G1 ); return; }
        if (I <= Ig) { setG( G2 ); return; }
        
        double U = ( I - Ig) / G3 + Us;
        setG( I / U );
    }
};

#endif // INCLUDE_1N4148_H_
