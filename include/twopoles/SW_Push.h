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

    SW_Push(const std::string & name) : TwoPole(name), _R(INF) {
        this->G = 0;
    }

    void press(bool b) {
        this->G = b ? INF : 0;
        // TODO
        this->update(p[1], p[2], true);
    }

    void toggle() {
    	press(true);
    	press(false);
    }
private:
    float _R;





public:
    R(const std::string & name, float r) : TwoPole(name), _R(r) {
    }

    void update(Pin & local, Pin & remote, NetSet * nets) {
        remote = State(local.U, 1.0 / (1.0/local.G + _R), -local.I);
    }

private:
    float _R;

};

#endif // _SW_Push_H_
