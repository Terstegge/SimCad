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

#include <iostream>
using std::cout;
using std::endl;

void Pin::connect_to(Pin & p) {
    if (this->_net != p._net) {
        // Merge the Pins into one Net
        this->_net->merge_net(this->_net, p._net);
    }
}

void Pin::operator = (State s) {
    Net::_id++;
    NetSet net1;
    setDrvState(s, &net1);
    while (net1.size()) {
        NetSet net2;
        for (shared_ptr<Net> n : net1) {
            n->update(nullptr, &net2);
        }
        net1 = net2;
    }
}

void Pin::setDrvState(State s, NetSet * nets) {
    if (_drv_state != s) {
        // Only change the driving state when a change is detected
        _drv_state  = s;
//        (*nets).insert(_net);
        if (_net) {
            if (nets) {
                // A NetSet is provided -> do not walk down
                // the whole circuit, but report the Net to
                // be updated instead.
                (*nets).insert(_net); //.push_back(_net);
            } else {
                // No NetSet is provided -> update Net
                // recursively
                _net->update(this, nullptr);
            }
        }
    }
}

