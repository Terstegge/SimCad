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
// is simulated without a voltage drop:
// If current could flow (A is positive or K is
// negative), the state change is propagated to
// the respective 'other' side, setting both,
// A and K, to the same state.
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

    State EVS_A;    // Equivalent Voltage Source for Anode
    State EVS_C;    // Equivalent Voltage Source for Cathode

public:
    Pin & A, & C;   // References for Anode and Cathode
    
    _1N4148(const string & name="") : TwoPole(name, R1), C(p[1]), A(p[2]) {
    }

    void calculate() override {
        // Check that we have a driving state on both sides.
        // If not, set the resistance for free floating case.
        if (A.getInpState() == NC || C.getInpState() == NC) {
            _R = R1;
            return;
        }
        // Calculate the EVS on both sides
        EVS_A = A.getEVS();
        EVS_C = C.getEVS();
        // Calculate internal resistance and no-load voltage
        float Ri = EVS_A._R + EVS_C._R;
        float Ul = EVS_A._U - EVS_C._U;
        // Check for negative or zero no-load voltage.
        // Set R1 in this case (diode non-conducting)
        if (Ul <= 0.0) {
            _R = R1;
            return;
        }
        // Check which resistance to use
        float Ik = Ul / Ri;
        float Ir = Ik * (1 - Us/Ul);
        float Is = Us / R2;

        if (Ir <= Is) {
            // Use R2 for voltages up to Us
            _R = R2;
        } else {
            // Calculate resistance for voltage > Us
            float t = Us * (R3 - R2);
            _R  = R2 * R3 * Ik - t;
            _R /= R2 * Ri * Ik + t;
            _R *= Ri;
        }
    }
};

#endif // INCLUDE_1N4148_H_
