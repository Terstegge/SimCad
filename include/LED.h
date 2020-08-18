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
    LED(const string & name="") : _1N4148(name) { }
    
    bool on() {
        return true;
        //(A.getNet()->getCurrent() ||
        //        K.getNet()->getCurrent()) &&
        //        (K.getInpState().toStrong() == LOW);
    }

};

#endif // _LED_H_
