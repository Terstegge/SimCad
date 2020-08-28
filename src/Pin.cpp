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
#include "Pin.h"

void Pin::connect_to(Pin & p) {
    // Check if both Pins are in the same Net already
    if (this->_netPtr != p._netPtr) {
        // Merge the Pins into one Net
        this->_netPtr->merge_net(this->_netPtr, p._netPtr);
    }
}

// Get the input state of a Pin
State Pin::getInpState() const {
    State s = getNetState();
    s /= _drvState;
    return s;
}

void Pin::setDrvState(State s, NetSet *nets) {
    // Only change the driving state when a change is detected
    if (_drvState != s) {
        _drvState  = s;
        if (nets) {
            nets->insert(_netPtr);
        } else {
            NetSet net1;
            net1.insert(_netPtr);
            while (net1.size()) {
                NetSet net2;
                for (std::shared_ptr<Net> n : net1) {
                    n->update(&net2);
                }
                net1 = net2;
            }
        }
    }
}

