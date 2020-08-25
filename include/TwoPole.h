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
// Base class for all kinds of two-poles (e.g.
// resistors and diodes). Currently only the
// DC resistance and voltage offset is stored.
//
#ifndef INCLUDE_TWOPOLE_H_
#define INCLUDE_TWOPOLE_H_

#include "Part.h"
#include "Pin.h"
#include "Narray.h"

class TwoPole : public Part {
public:
    Narray<Pin, 3> p;
    float         _R;  // TwoPole DC resistance
    float         _U;  // TwoPole voltage offset

    TwoPole(const std::string & name)
    : Part(name), NAME(p), _R(INF), _U(0.0)
    {
        // Set the part pointers
        p[1].setPartPtr(this);
        p[2].setPartPtr(this);
        // Attach handlers
        p[1].attach([this](NetSet * nets) {
            // Check for disconnect
            if (p[1].getInpState().isNC()) {
                p[2].setDrvState(State(), nets);
                return;
            }
            update(p[1], p[2], calculate(), 1.0, nets);
        });
        p[2].attach([this](NetSet * nets) {
            // Check for disconnect
            if (p[2].getInpState().isNC()) {
                p[1].setDrvState(State(), nets);
                return;
            }
            update(p[2], p[1], calculate(), -1.0, nets);
        });
    }

    virtual ~TwoPole() {
    }

    // The method to calculate the new parameters
    // (_R and _U) of the TwoPole. If the values
    // have changed, the method returns true.
    virtual bool calculate() = 0;

    // Utility method to update the drive states
    // of the TwoPole. If the parameter 'changed'
    // is true, the change will also propagated
    // to the local side.
    void update(Pin & local, Pin & remote, bool changed,
                float polarity=0.0,  NetSet * nets=nullptr)
    {
        State s = local.getInpState();
        s._G  = 1.0 / ( 1.0/s._G + _R);
        s._U += polarity * _U;
        remote.setDrvState( s, nets);
        if (changed) {
            s = remote.getInpState();
            s._G  = 1.0 / ( 1.0/s._G + _R);
            s._U += -polarity * _U;
            local.setDrvState( s, nets);
        }
    }

};

#endif // INCLUDE_TWOPOLE_H_
