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
#include "Net.h"
#include "Pin.h"
#include "TwoPole.h"
#include "ShortCircuitEx.h"

int Net::_no_nets = 0;
int Net::_short_circuit_count = 0;

#include <iostream>

bool Net::update(NetSet *nets, bool force) {
    Pin * first  {nullptr}; // Pointer to first ideal voltage source
    Pin * second {nullptr}; // Pointer to second ideal voltage source
    float u {0}, g {0}, i {0};

    for (Pin * p : _pins) {
        if (p->Gd != INF) {           // No ideal voltage source?
            g += p->Gd;              // Normal case: Sum up G and I
            i += p->Gd * p->Ud + p->Id;         //p->Gd ? p->Gd * p->Ud : p->Id;
        } else {
            if (!first) {               // Ideal Voltage source
                u = p->Ud;           // Store NET voltage
                g = INF;
                first = p;              // Store pointer to first VS
                continue;
            } else {
                if (p->Ud != u) {     // Did we find a different voltage source?
                    second = p;         // Different VS was found, store it
                    break;
                }
            }
        }
    }
    if (first && second) {              // Check for short circuit...
        short_circuit_exception e(first, second);
        throw e;
    }
    if ((g != 0.0) && (g != INF)) {
        u = i / g;       // Calculate resulting voltage
    }

    // Check if the State of the Net has changed
    if (U != u || Gi != g || Is != i || force) {
        U  = u;
        Gi = g;
        Is = i;

        std::cout << "Changed State!" << std::endl;
        std::cout << this << std::endl;

        for (Pin * p : _pins) {
            p->update(nets);
        }
        return true;
    }
    return false;
}

void Net::update(bool force) {
    NetSet nset1, nset2;
    update(&nset1, force);
    while (nset1.size()) {
        nset2.clear();
        for (NetPtr n : nset1) {
            n->update(&nset2);
        }
        nset1 = nset2;
    }
}


ostream & operator << (ostream & os, const NetPtr net)
{
    os << "Net " << net->_name;
    os << "[" << net->U      << " V, "
              << 1.0/net->Gi << " Ω]"
              << std::endl;
    for (Pin * p : net->_pins) {
        os << "  driven by "
           << drive << (*p) << std::endl;
    }
    return os;
}

