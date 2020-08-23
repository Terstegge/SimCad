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
// DC resistance is stored.
//
#ifndef INCLUDE_TWOPOLE_H_
#define INCLUDE_TWOPOLE_H_

#include "Part.h"
#include "Pin.h"
#include "Narray.h"

class TwoPole : public Part {
public:
    Narray<Pin, 3> p;
    float         _R; // TwoPole DC resistance

    TwoPole(const std::string & name, float r)
    : Part(name), NAME(p), _R(r)
    {
        // Set the part pointers
        p[1].setPartPtr(this);
        p[2].setPartPtr(this);
        // Attach handlers
        p[1].attach([this](NetSet & nets) {
            // Check for disconnect
            if (p[1].getInpState() == NC) {
                p[2].setDrvState(NC, nets);
                return;
            }
            // Calculate the new R
            float old_R = _R;
            this->calculate();
            // Set remote side
            State remote(p[1].getInpState()._U, _R);
            p[2].setDrvState( remote, nets);
            // Set local side if R changed
            if (old_R != _R) {
                State local(p[2].getInpState()._U, _R);
                p[1].setDrvState(local, nets);
            }
        });
        p[2].attach([this](NetSet & nets) {
            // Check for disconnect
            if (p[2].getInpState() == NC) {
                p[1].setDrvState(NC, nets);
                return;
            }
            // Calculate the new R
            float old_R = _R;
            this->calculate();
            // Set remote side
            State remote(p[2].getInpState()._U, _R);
            p[1].setDrvState( remote, nets);
            // Set local side if R changed
            if (old_R != _R) {
                State local(p[1].getInpState()._U, _R);
                p[2].setDrvState(local, nets);
            }
        });
    }

    virtual ~TwoPole() {
    }

    // The method to calculate the new resistance
    // of the TwoPole, which will be stored in _R.
    // The method has access to the Pin members
    // p[1] and p[2], if needed.
    virtual void calculate() = 0;

    // Utility method to get the
    // other side of the TwoPole
    Pin * other(Pin * pin) {
        return (pin == &p[1]) ? &p[2] : &p[1];
    }
};

#endif /* INCLUDE_TWOPOLE_H_ */
