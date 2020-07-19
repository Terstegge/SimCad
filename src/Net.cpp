#include <ShortCircuitEx.h>
#include "Net.h"
#include "Pin.h"

int Net::_no_nets = 0;
int Net::_short_circuit_count = 0;


void Net::merge_net(NetPtr n, NetPtr o) {
    // Insert the Pin pointers to our vector. The
    // Net pointers in the Pins are not changed!
    _pins.insert(_pins.end(), o->_pins.begin(), o->_pins.end() );
    // Set the Net pointers in the new entries
    for (Pin * p : o->_pins) {
        p->_net = n;
    }
    if (!update(nullptr)) {
        // If no update was needed, update at least the new Pins
        for (Pin * p : o->_pins) {
            p->update(nullptr);
        }
    }
}

bool Net::update(NetSet * nets) {
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
                cout << "new SC" << endl;
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
        _state = s;
        for (Pin * p : _pins) {
            p->update(nets);
        }
        return true;
    }
    return false;
}

State Net::calculate_state() const {
    State res   = NC;       // The result State
    Pin * first = nullptr;  // First driving Pin
    // Loop over all connected Pins and update result
    for (Pin * p : _pins) {
        switch(p->getDrvState()) {
            case NC: {   // Ignore "Not Connected" Pins
                break;
            }
            case LOW: {
                if (res != HIGH) {
                    res  = LOW;
                    first = p;
                    break;
                } else {
                    cout << *p << endl;
                    throw short_circuit_exception(first, p);
                }
            }
            case HIGH: {
                if (res != LOW) {
                    res  = HIGH;
                    first = p;
                    break;
                } else {
                    cout << *p << endl;
                    throw short_circuit_exception(first, p);
                }
            }
        }
    }
    return res;
}

ostream & operator << (ostream & os, const NetPtr net)
{
    os << net->_name << ": "  << endl;
    for (Pin * p : net->_pins) {
        os << *p << " (driving " << (*p).getDrvState() << ")" << ", " << endl;
    }
    return os;
}

