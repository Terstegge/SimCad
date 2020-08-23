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
#include "ShortCircuitEx.h"
#include "Pin.h"
#include "TwoPole.h"

void Pin::connect_to(Pin & p) {
    // Check if both Pins are in the same Net already
    if (this->_netPtr != p._netPtr) {
        // Merge the Pins into one Net
        this->_netPtr->merge_net(this->_netPtr, p._netPtr);
    }
}

// Get Equivalent Voltage Source (EVS)
State Pin::getEVS() {
    float G  = 0.0;
    float Ik = 0.0;
    bool summed = false;

    // Step into the net
    for (Pin * pp : _netPtr->_pins) {
        // Skip over entry Pin
        if (pp == this) continue;
        // Immediately return strong Pins
        State s = pp->getDrvState();
        if (s.isStrong()) return s;
        // Only process TwoPoles
        TwoPole * tp = dynamic_cast<TwoPole*>(pp->getPartPtr());
        if (!tp) continue;
        // Get other side of TwoPole
        Pin * other = tp->other(pp);
        // Skip TwoPols which are not driven remotely
        State other_s = other->getInpState();
        if (other_s == NC) continue;
        // Check if remote side is strong
        if (other_s.isStrong()) {
            float g = 1.0/tp->_R;
            G  += g;
            Ik += g * other_s._U;
            summed = true;
        } else {
            // Recurse
            State evs = other->getEVS();
            float g = 1.0 / (tp->_R + evs._R);
            G  += g;
            Ik += g * evs._U;
            summed = true;
        }
    }
    State result = NC;
    if (summed) {
        result._R =  1.0/G;
        result._U = (Ik == 0.0 & G == 0.0) ? 0.0 : (Ik / G);
    }
    return result;
}


void Pin::setDrvState(State s, NetSet & nets) {
    // Only change the driving state when a change is detected
    if (_drvState != s) {
        _drvState  = s;
        nets.insert(_netPtr);
    }
}

void Pin::operator = (State s) {
    NetSet net1;
    setDrvState(s, net1);
    while (net1.size()) {
        NetSet net2;
        for (std::shared_ptr<Net> n : net1) {
            n->update(net2);
        }
        net1 = net2;
    }
}

