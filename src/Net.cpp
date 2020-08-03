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
    // Sum the States of all connected Pins
    int state_count[6] = { 0 };
    int total_count    =   0;
    for (Pin * p : _pins) {
        state_count[ p->getDrvState() ]++;
        total_count++;
    }
    // Pin(s) driving LOW
    if (state_count[ LOW ] && !state_count[ HIGH ]) {
        return LOW;
    } 
    // Pin(s) driving HIGH
    if (state_count[ HIGH ] && !state_count[ LOW ]) {
        return HIGH;
    } 
    // Short circuit
    if (state_count[ HIGH ] && state_count[ LOW ]) {
        Pin * low = nullptr, * high = nullptr;
        for (Pin * p : _pins) {
            if ((p->getDrvState() == LOW)  && !low ) low  = p;
            if ((p->getDrvState() == HIGH) && !high) high = p;
            throw short_circuit_exception(low, high);
        }
    }
    // Pin(s) pulling down        
    if (state_count[ PD ] && !state_count[ PU ]) {
        return PD;
    } 
    // Pin(s) pulling up
    if (state_count[ PU ] && !state_count[ PD ]) {
        return PU;
    } 
    // Both pulls at the same time...
    if (state_count[ PD ] && state_count[ PU ]) {
        Pin * pd = nullptr, * pu = nullptr;
        for (Pin * p : _pins) {
            if ((p->getDrvState() == PD) && !pd) pd = p;
            if ((p->getDrvState() == PU) && !pu) pu = p;
            throw short_circuit_exception(pd, pu);
        }
    }
    // No driving Pins
    return NC;
}

ostream & operator << (ostream & os, const NetPtr net)
{
    os << net->_name << ": "  << endl;
    for (Pin * p : net->_pins) {
        os << *p << " (driving " << (*p).getDrvState() << ")" << ", " << endl;
    }
    return os;
}

