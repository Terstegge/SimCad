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
//  (c) 2021  A. Terstegge
//
///////////////////////////////////////////////
//
#include "Net.h"
#include "Pin.h"
#include "TwoPole.h"
#include "ShortCircuitEx.h"

int Net::_no_nets = 0;

#include <iostream>
#include <cmath>

void Net::merge_net(NetPtr n, NetPtr o) {
    // Both Nets are the same?
    if (n == o) return;
    // Insert the Pin pointers to our vector. The
    // Net pointers in the Pins are not changed!
    _pins.insert(_pins.end(), o->_pins.begin(), o->_pins.end() );
    // Set the Net pointers in the new entries
    for (Pin * p : o->_pins) {
        p->setNetPtr(n);
    }
    update();
}

void Net::update(ElementSet *esp) {
	Pin * ivs_ptr {nullptr};            // Pointer to first ideal voltage source
    double gs {0}, is {0}, id {0};

    for (Pin * p : _pins) {
        // Skip non-driving Pins
        if (p->isDrvNC()) continue;
        if (p->Gd != INF) {           // No ideal voltage source?
            gs += p->Gd;              // Normal case: Sum up G and I
            is += p->Gd * p->Ud;
            id += p->Id;
        } else {
            if (!ivs_ptr) {           // Ideal Voltage source
                ivs_ptr = p;          // Store pointer to first VS
                continue;
            } else {
                if (p->Ud != ivs_ptr->Ud) {     // Did we find a different voltage source?
                    short_circuit_exception e(ivs_ptr, p);
                    throw e;
                }
            }
        }
    }

    double u {0}, gi {0};
    if (ivs_ptr) {
        u = ivs_ptr->Ud;
        gi = INF;
    } else {
        u =  gs ? (is+id) / gs : 0;
        gi = gs;
    }

    bool U_diff = fabs(_U - u) > 1e-5;
    bool G_diff = fabs(_Gi - gi) > 1e-5;
    bool I_diff = fabs(_Id - id) > 1e-5;
    //if (U_diff || G_diff || I_diff ) {
    // Note that the valuea might be INF, and the
    // X_diff vars give wrong values!!!!
        
    // Check if the State of the Net has changed
    if (_U != u || _Gi != gi || _Id != id ) {
        _U  = u;
        _Gi = gi;
        _Id = id;
        _Gs = gs;

        for (Pin * p : _pins) {
            p->update(esp);
        }
    }
}


void Net::update() {
    ElementSet nset1, nset2;
    update(&nset1);
    while (nset1.size()) {
        nset2.clear();
        for (ElementPtr n : nset1) {
            n->update(&nset2);
        }
        nset1 = nset2;
    }
}


ostream & operator << (ostream & os, const NetPtr net)
{
    os << "Net " << net->getName();
    os << "[" << net->U      << " V, "
              << 1.0/net->Gi << " Ω, "
              << net->Id     << " A]"
              << std::endl;
    for (Pin * p : net->_pins) {
        os << "  driven by "
           << drive << (*p) << std::endl;
    }
    return os;
}

