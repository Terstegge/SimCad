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

class LED : public _1N4148 {
public:
    LED(const std::string & name="") : _1N4148(name) {
    }
    
    bool on() {
        State a = A.getNetState();
        State c = C.getNetState();
        // Check if both sides are driven.
        // If not the LED is off!
        if (a.isNC() || c.isNC()) {
            return false;
        }
        // LED is on if more than 5mA flow.
        return ((a - c).getU() / _trans.getR()) > 0.005;
    }
};

#endif // _LED_H_
