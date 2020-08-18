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
int Net::_id = 0;

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

void Net::merge_net(NetPtr n, NetPtr o) {
    // Insert the Pin pointers to our vector. The
    // Net pointers in the Pins are not changed!
    _pins.insert(_pins.end(), o->_pins.begin(), o->_pins.end() );
    // Set the Net pointers in the new entries
    for (Pin * p : o->_pins) {
        p->setNet(n);
    }
//    _id++;
    if (!update(nullptr, nullptr)) {
        // If no update was needed, update at least the new Pins
        for (Pin * p : o->_pins) {
//            _id++;
            p->update(nullptr);
        }
    }
}

bool Net::update(Pin * src, NetSet * nets) {
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
                cout << "new SC" << std::endl;
                _short_circuit = true;
                ++_short_circuit_count;
                return false;
            }
        }
        return false;
    }

    if (_short_circuit) {
        cout << "clear SC" << endl;
        _short_circuit = false;
        --_short_circuit_count;
    }

    // Check if the State of the Net has changed
    if (s != _state) {
        // Set the State and call update on every Pin

//        cout << _name << ": " << s << " not " << _state << endl;

        _state = s;
//        _id++;
            for (Pin * p : _pins) {
//                _id++;
                p->update(nets);
            }
        return true;
    }
    return false;
}


State Net::calculate_state() {

//    cout << "Calculate " << _name << endl;

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
                if (!tp) {
                //                cout << "Not a R :( " << endl;
                    continue;
                }


                float G = 1 / tp->TP_R; // s.getR();
                Gi += G;
                Ik += s.getU() * G;
                summed = true;
            }
        }
    }
    // Set the result
    if (summed) {
        res.setNC(false);
        res.setU (Ik  / Gi);
        if (res.getU() < 1e-6) res.setU(0);
        res.setR (1.0 / Gi);
    }

    return res;


#if 0
    // Sum the States of all connected Pins
    int state_count[6] = { 0 };
    for (Pin * p : _pins) {
        state_count[ p->getDrvState() ]++;
    }
    // HIGH and LOW: Short circuit
    if (state_count[ HIGH ] && state_count[ LOW ]) {
        Pin * low = nullptr, * high = nullptr;
        for (Pin * p : _pins) {
            if ((p->getDrvState() == LOW)  && !low)  low  = p;
            if ((p->getDrvState() == HIGH) && !high) high = p;
        }
        throw short_circuit_exception(low, high);
    }
    // Pin(s) driving LOW
    if (state_count[ LOW ]) {
        _current_flow = state_count[ PU ];
        return LOW;
    }
    // Pin(s) driving HIGH
    if (state_count[ HIGH ]) {
        _current_flow = state_count[ PD ];
        return HIGH;
    }
    // Both pulls at the same time...
    if (state_count[ PD ] && state_count[ PU ]) {
        _current_flow = true;
        return state_count[ PU ] >= state_count[ PD ] ? PU : PD;
    }
    // Pin(s) pulling down        
    if (state_count[ PD ]) {
        return PD;
    } 
    // Pin(s) pulling up
    if (state_count[ PU ]) {
        return PU;
    } 
    // No driving Pins
    return NC;
#endif
}

ostream & operator << (ostream & os, const NetPtr net)
{
    os << net->_name << ": (generating input state " << net->getState() << ")"  << endl;
//    bool first = true;
    for (Pin * p : net->_pins) {
//        if (first) {
//            first = false;
//            continue;
//        }
        os << *p << " (driving " << (*p).getDrvState() << ")" << ", " << std::endl;
    }
    return os;
}

