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
#ifndef INCLUDE_1N4148_H_
#define INCLUDE_1N4148_H_

#include "TwoPole.h"
#include "R.h"

#include <iostream>
using namespace std;

class _1N4148 : public TwoPole {
protected:
    //////////////////////
    // Diode configuration
    //////////////////////
    const float Us = 0.7;     // Forward voltage
    const float R1 = 100000;  // Resistance up to 0V and for free floating case
    const float R2 = 280;     // Resistance up to Us
    const float R3 = 1;       // Resistance from Us on

public:
    Pin & A, & C;   // References for Anode and Cathode
    
    _1N4148(const string & name="") : TwoPole(name), C(p[1]), A(p[2]) {
        // Set default resistance
        _trans.setR(R1);
    }

    bool calculate() override {
        float old_R = _trans.getR();
        State a = A.getInpState();
        State c = C.getInpState();

        // Check that we have a driving state on both sides.
        // If not, set the resistance for free floating case.
        if (a.isNC() || c.isNC()) {
            _trans.setR(R1);
            return (_trans.getR() != old_R);
        }
        // Calculate internal resistance and no-load voltage
        float Ri = a.getR() + c.getR();
        float Ul = a.getU() - c.getU();
        // Check for negative or zero no-load voltage.
        // Set R1 in this case (diode non-conducting)
        if (Ul <= 0.0) {
            _trans.setR(R1);
            return (_trans.getR() != old_R);
        }
        // Check which resistance to use
        float Ik = Ul / Ri;
        float Ir = Ik * (1 - Us/Ul);
        float Is = Us / R2;

        if (Ir <= Is) {
            // Use R2 for voltages up to Us
            _trans.setR(R2);
        } else {
            // Calculate resistance for voltage > Us
            float t = Us * (R3 - R2);
            float R;
            R  = R2 * R3 * Ik - t;
            R /= R2 * Ri * Ik + t;
            R *= Ri;
            _trans.setR(R);
        }
        return (_trans.getR() != old_R);
    }
};

#endif // INCLUDE_1N4148_H_
