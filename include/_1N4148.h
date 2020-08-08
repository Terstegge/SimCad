#ifndef _1N4148_H_
#define _1N4148_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class _1N4148 : public Named {
public:
    Narray<Pin, 3> p;
    Pin & K, & A;
    
    // A diode is simulated as a piece of wire:
    // If current could flow (A is positive or
    // K is negative), the state change is
    // propagated to the 'other' side.
    _1N4148(const string & name="") :
        Named(name), NAME(p), K(p[1]), A(p[2])
    {
        K.attach([this](NetSet * nets){
            State k = (State)K;
            A.setDrvState( (k==LOW || k==PD) ? k : NC, nets);
        });
        A.attach([this](NetSet * nets){
            State a = (State)A;
            K.setDrvState( (a==HIGH || a==PU) ? a : NC, nets);
        });
    }
};

#endif // _1N4148_H_
