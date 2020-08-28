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

    TwoPole(const std::string & name) : Part(name), NAME(p) {
        // Set the part pointers
        p[1].setPartPtr(this);
        p[2].setPartPtr(this);
        // Attach handlers
        p[1].attach([this](NetSet * nets) { update(p[1], p[2], calculate(), nets); });
        p[2].attach([this](NetSet * nets) { update(p[2], p[1], calculate(), nets); });
    }

    virtual ~TwoPole() {
    }

    // The method to calculate the new state
    // (U/R/I) of the TwoPole. If the values
    // have changed, the method returns true.
    virtual bool calculate() = 0;

    // Utility method to update the drive states
    // of the TwoPole. If the parameter 'changed'
    // is true, the change will also propagated
    // to the local side.
    void update(Pin & local, Pin & remote, bool changed=false, NetSet * nets=nullptr)
    {
        remote.setDrvState(local.getInpState() + _trans, nets);
        if (changed) {
            local.setDrvState(remote.getInpState() + -_trans, nets);
        }
    }

protected:
    State   _trans;
};

#endif // INCLUDE_TWOPOLE_H_
