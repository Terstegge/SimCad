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
// Low-level implementation of a resistor, which
// will propagate a state change as the respective
// weak state to the 'other' side.
//
#ifndef _R_H_
#define _R_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class R : public Named {

public:
    Narray<Pin, 3> p;
    int id = 0;

    R(const string & name) : Named(name), NAME(p)
    {
        p[1].attach([this](NetSet * nets) {
            // Make sure the update is always only in
            // one direction during one transaction.
            if (Net::_id == id) return;
            id = Net::_id;
            p[2].setDrvState( toWeak((State)p[1]), nets );
        });
        p[2].attach([this](NetSet * nets) {
            // Make sure the update is always only in
            // one direction during one transaction.
            if (Net::_id == id) return;
            id = Net::_id;
            p[1].setDrvState( toWeak((State)p[2]), nets );
        });
    }

};

#endif // _R_H_
