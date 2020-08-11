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
// Low-level implementation of a simple switch.
// When on, both input states are propagated
// to the respective 'other' side.
//
#ifndef _SW_SPST_H_
#define _SW_SPST_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class SW_SPST : public Named {

public:
    Narray<Pin, 3> p;
    Pin * weak_pin = nullptr;
    bool _on;

    SW_SPST(const string & name)
    : Named(name), NAME(p), _on(false) {
        p[1].attach([this](NetSet * nets) {
//            if (_on) p[2].setDrvState((State)p[1], nets);
        });
        p[2].attach([this](NetSet * nets) {
//            if (_on) p[1].setDrvState((State)p[2], nets );
        });
    }

    void on() {
        if (_on) return;
        _on = true;
    	p[1] = (State)p[2];
    	p[2] = (State)p[1];
    }

    void off() {
        if (!_on) return;
        _on = false;
    	p[1] = NC;
    	p[2] = NC;
    }
};

#endif // _SW_SPST_H_
