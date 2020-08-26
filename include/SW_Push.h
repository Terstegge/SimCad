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
// Low-level implementation of a push button.
// The button is a TwoPole, which has a 
// resistance of 0 or INF Ohm.
//
#ifndef _SW_Push_H_
#define _SW_Push_H_

#include "TwoPole.h"

class SW_Push : public TwoPole {

public:

    SW_Push(const std::string & name) : TwoPole(name) {
    }

    bool calculate() override {
        return false;
    }

    void press(bool b) {
        _R = b ? 0 : INF;
        this->update(p[1], p[2], true);
    }

    void toggle() {
    	press(true);
    	press(false);
    }

};

#endif // _SW_Push_H_
