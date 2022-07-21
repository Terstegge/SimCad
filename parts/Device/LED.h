///////////////////////////////////////////////
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
///////////////////////////////////////////////
//
// Low-level implementation of a LED, which
// behaves similar to a diode (see 1N4118).
// The method on() checks if current is flowing
// and the LED is on.
//
#ifndef _PARTS_DEVICE_LED_H_
#define _PARTS_DEVICE_LED_H_

#include "DIODE.h"

class LED : public DIODE {
public:
    LED(const std::string & name="") : DIODE(name, 2.0) { }

    inline bool on() {
        return A.I() > 0.005;
    }
};

#endif // _PARTS_DEVICE_LED_H_
