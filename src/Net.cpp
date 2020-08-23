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
#include <ShortCircuitEx.h>
#include "Net.h"
#include "Pin.h"
#include "TwoPole.h"

int Net::_no_nets = 0;
int Net::_short_circuit_count = 0;

#include <iostream>

void Net::merge_net(NetPtr n, NetPtr o) {
    // Insert the Pin pointers to our vector. The
    // Net pointers in the Pins are not changed!
    _pins.insert(_pins.end(), o->_pins.begin(), o->_pins.end() );
    // Set the Net pointers in the new entries
    for (Pin * p : o->_pins) {
        p->setNetPtr(n);
    }
    // Update the Net
    NetSet net1;
    update(net1);
    if (net1.size() == 0) {
        // At least update the new Pins
        for (Pin * p : o->_pins) {
            p->update(net1);
        }
    }
    while (net1.size()) {
        NetSet net2;
        for (std::shared_ptr<Net> n : net1) {
            n->update(net2);
        }
        net1 = net2;
    }
}

bool Net::update(NetSet & nets) {
    State s;
    try {
        // Calculate the State of the Net
        s =  calculate_state();
    } catch(short_circuit_exception & ex) {
        if (_short_circuit) {
            // The Net was marked a SC before...
            return false;
        } else {
            // Check if we are in a transaction
            if (true) { //Pin::set_depth == 0) {
                // No transaction->rethrow
                throw ex;
            } else {
                // Mark this Net as SC
                std::cout << "new SC" << std::endl;
                _short_circuit = true;
                ++_short_circuit_count;
                return false;
            }
        }
        return false;
    }

    if (_short_circuit) {
        std::cout << "clear SC" << std::endl;
        _short_circuit = false;
        --_short_circuit_count;
    }

    // Check if the State of the Net has changed
    if (s != _state) {
        // Set the State and call update on every Pin
        _state = s;
        for (Pin * p : _pins) {
            p->update(nets);
        }
        return true;
    }
    return false;
}


State Net::calculate_state() {
//    cout << "Calculate net " << _name << endl;
    // Default NC
    State res  = NC;
    Pin * last = nullptr;
    bool  sum  = true;
    bool  summed = false;

    float Gi = 0;
    float Ik = 0;
    
    // Loop over all Pins
    for (Pin * p : _pins) {
        // Get the driving state
        State s = p->getDrvState();
        // Ignore NC
        if (s == NC) continue;
        // Check for strong pins
        if (s.isStrong()) {
            // Check for short circuit
            if (res.isStrong() && (s != res)) {
                throw short_circuit_exception(last, p);
            }
            res = s;
            sum = false;
            summed = false;
        } else {
            // Check if we need to sum
            if (sum) {
                TwoPole * tp = dynamic_cast<TwoPole*>(p->getPartPtr());
                if (!tp) continue;
                float g = 1.0 / tp->_R;
                Gi += g;
                Ik += g * s._U;
                summed = true;
            }
        }
    }
    // Set the result
    if (summed) {
        res._U = Ik / Gi;
        res._R = 1. / Gi;
    }
    return res;
}

ostream & operator << (ostream & os, const NetPtr net)
{
    os << "Net " << net->_name << ": " << net->getState() << std::endl;
    for (Pin * p : net->_pins) {
        os << " " << p->getName() << " driving " << p->getDrvState() << std::endl;
    }
    return os;
}
