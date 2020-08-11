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
#ifndef _1N4148_H_
#define _1N4148_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class _1N4148 : public Named {
public:
    Narray<Pin, 3> p;
    Pin & K, & A;
    int id = 0;
    
    _1N4148(const string & name="") :
        Named(name), NAME(p), K(p[1]), A(p[2])
    {
        K.attach([this](NetSet * nets){
            // Make sure the update is always only in
            // one direction during one transaction.
            if (Net::_id == id) return;
            id = Net::_id;
            State k = (State)K;
            A.setDrvState( (k==LOW || k==PD) ? k : NC, nets);
        });
        A.attach([this](NetSet * nets){
            // Make sure the update is always only in
            // one direction during one transaction.
            if (Net::_id == id) return;
            id = Net::_id;
            State a = (State)A;
            K.setDrvState( (a==HIGH || a==PU) ? a : NC, nets);
        });
    }
};

#endif // _1N4148_H_
