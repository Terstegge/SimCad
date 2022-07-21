/////////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
/////////////////////////////////////////////////
//
#include "Net.h"
#include "Pin.h"
#include "TwoPole.h"
#include "SimCadException.h"
#include <iostream>
#include <cmath>

// Static members
int  Net::_no_nets = 0;
bool Net::_enable_sc_exceptions = true;;

void Net::merge_net(Net * n, Net * o) {
    // Both Nets are the same?
    if (n == o) return;
    // Insert the Pin pointers to our vector. The
    // Net pointers in the Pins are not changed!
    _pins.insert(_pins.end(), o->_pins.begin(), o->_pins.end() );
    // Set the Net pointers in the new entries
    for (Pin * p : o->_pins) {
        p->_netPtr = n;
    }
    // Delete the old Net
    delete o;
    update();
}

void Net::update() {
    NetSet set1, set2;
    update(&set1);
    while (set1.size()) {
        set2.clear();
        for (auto elem : set1) {
            elem->update(&set2);
        }
        set1 = set2;
    }
}

void Net::update(NetSet * nset) {
    Pin * ivsPtr = nullptr;     // Pointer to first ideal voltage source
    double Gtot  = 0.0;         // Total Net conductivity
    double Gload = 0.0;         // Net conductivity excluding voltage sources
    // Iterate over all Pins in the Net
    for (Pin * p : _pins) {
        // Skip non-driving Pins
        if (p->isDrvNC()) continue;
        // Add up conductivity
        Gtot += 1 / p->_Rdrv;
        // Check for voltage source
        if (p->isDrvVS()) {
            if (!ivsPtr) {      // Check if it is the first voltage
                ivsPtr = p;     // source and set the pointer
                continue;
            } else {
                // We found a second voltage source
                if (_enable_sc_exceptions) {
                    if (p->_Udrv != ivsPtr->_Udrv) {
                        // Did we find a different voltage source?
                        throw shortCircuitException(this);
                    }
                }
            }
        } else {
            // No voltage source -> add up load conductivity
            Gload += 1 / p->_Rdrv;
        }
    }

    // Calculate the total and load resistance
    double Rtot  = 1 / Gtot;
    double Rload = 1 / Gload;

    // Calculate new voltage of the Net. Either it is driven
    // by a voltage source (taking the voltage of this source),
    // or the voltage is calculated by the resulting Isum() function.
    double U = 0;
    if (ivsPtr) {
        U = ivsPtr->_Udrv;
    } else {
        if (Gload != 0.0) {
            U  = zero( [&](double U) -> double { return Isum(U); } );
        }
    }

    // Check if the State of the Net has changed,
    // and update all Pins in the Net in this case
    if (_U != U || _Rtot != Rtot) {
        // Set new values
        _U     = U;
        _Rtot  = Rtot;
        _Rload = Rload;
        // Update all Pins in the Net
        for (Pin * p : _pins) {
            p->update(nset);
        }
    }
}

// Calculate the current flowing to/from this Net.
// Positive currents flow into this Net, negative
// currents flow out of the Net. If the second parameter
// is used, a specific Pin is excluded from the calculation.
// If it is not used, all voltage sources are excluded from
// the calculation.
double Net::Isum(double U, const Pin * p) const {
    double res = 0;
    for (Pin * pin : _pins) {
        if (!p && pin->isDrvVS()) continue;
        if (pin != p && pin->_Idrv) {
            res += pin->_Idrv(U);
        }
    }
    return res;
}


double Net::Rw(const Pin * p) const {
    if (isNC()) return INF;
    double G = 0;
    for (Pin * pin : _pins) {
        if (pin != p) {
            if (pin->isDrvNC()) continue;
            if (pin->isDrvVS()) return 0;
            G += 1/pin->_Rdrv;
        }
    }
    return 1/G;
}

// Stream output operator showing the Net state and the driving Pins
std::ostream & operator << (std::ostream & os, const Net * net)
{
    os << "Net: " << net->getName();
    if (net->isNC())  os << " NC ";
    if (net->isVS())  os << " VS ";
    os << "[" << net->U  << " V, "
              << net->R  << " Ohm]"
              << std::endl;
    for (Pin * p : net->_pins) {
        if (p->isDrvNC()) continue;
        os << "  driven by "
           << drive << (*p)
           << std::endl;
    }
    return os;
}

// Sign function. Not available in standard library,
// so define it here.
int Net::sgn(double v) {
    return (v > 0) - (v < 0);
}

// Find a zero in function f(x) using a combination of
// the bisection and secant method. Both methods need
// to evaluate f(x) only once per iteration. The bisection
// method is used to get a first rough estimate of the
// interval [x1,x2] in which the zero is located. The
// second step is using the secant method because of
// better convergence. Using only the secant method
// leads to problems in cases where f(x) has a very
// small or high slope.
double Net::zero(std::function<double(double)> f) {
    double x1  = SUPPLY_GROUND;
    double fx1 = f(x1);
    double x2  = SUPPLY_VOLTAGE;
    double fx2 = f(x2);
    double x3, fx3;
    // Handle special case when f(x) has slope 0
    if (fx1 == fx2) return 0;
    // bisection algorithm
    while ((x2-x1) > 0.3) {
        x3  = (x2+x1) / 2.0;
        fx3 = f(x3);
        if (sgn(fx1) == sgn(fx3)) {
            x1 = x3;
        } else {
            x2 = x3;
        }
    }
    // secant algorithm
    fx1 = f(x1);
    fx2 = f(x2);
    while (fabs(fx2) > 1e-10) {
        x3  = x2 - ((x2 - x1) / (fx2 - fx1)) * fx2;
        x1  = x2;
        x2  = x3;
        fx1 = fx2;
        fx2 = f(x3);
    }
    // Truncate after 8 decimal places
    return trunc(x2 * 10e8) / 10e8;
}
