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
// Low-level implementation of a LED, which
// behaves similar to a diode (see 1N4118).
// The method on() checks if current is flowing
// and the LED is on.
//
#ifndef _LED_H_
#define _LED_H_

#include "_1N4148.h"

#include <iostream>
using namespace std;

class LED : public _1N4148 {
public:
    LED(const std::string & name="") : _1N4148(name) {
    }
    
    bool on() {
        // Check if both sides are driven.
        // If not the LED is off!
        if (this->EVS_A == NC || this->EVS_C == NC) {
            return false;
        }
        float U = this->EVS_A._U - this->EVS_C._U;
        float R = this->EVS_A._R + this->EVS_C._R + _R;
        // Diode is on if voltage is 5mA at least;

        cout << (U/R) << endl;

        return (U / R) >= 0.005;
    }
};

#endif // _LED_H_
