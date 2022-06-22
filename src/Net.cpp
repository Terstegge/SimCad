///////////////////////////////////////////////
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
///////////////////////////////////////////////
//
#include "Net.h"
#include "Pin.h"
#include "TwoPole.h"
#include "SimCadException.h"
int Net::_no_nets = 0;
#include <iostream>
#include <cmath>
#include <cassert>

bool Net::_enable_sc_exceptions = true;;

using entry = std::pair <Pin *, std::function<double(double)>>;


int sgn(double v) {
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
    double x1  = 0.0;
    double fx1 = f(x1);
    double x2  = 5.0;
    double fx2 = f(x2);
    double x3, fx3;

    // Handle special case when f(x) has slope 0
    if (fx1 == fx2) return 0;

    while ( (x2-x1) > 0.1 ) {
        x3  = (x2+x1) / 2.0;
        fx3 = f(x3);
        if (sgn(fx1) == sgn(fx3)) {
            x1 = x3;
        } else {
            x2 = x3;
        }
    }
    fx1 = f(x1);
    fx2 = f(x2);
    while (fabs(fx2) > 1e-10) {
        x3 = x2 - ((x2 - x1) / (fx2 - fx1)) * fx2;
        x1 = x2;
        x2 = x3;
        fx1 = fx2;
        fx2 = f(x3);
    }
    // Truncate after 8 decimal places
    return trunc(x2 * 10e8) / 10e8;
}

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
    //	std::cout << "Net::update()" << std::endl;

    //    if (getName().find("__R") != std::string::npos)
    //        std::cout << "update Net " << getName() << std::endl;
    _mutex.lock();
    NetSet set1, set2;
    update(&set1);
    while (set1.size()) {
        set2.clear();
        for (auto elem : set1) {
            elem->update(&set2);
        }
        set1 = set2;
    }
    _mutex.unlock();
}

void Net::update(NetSet * usp) {

    // std:: cout << "update " << getName() << std::endl;
    Pin * ivs_ptr {nullptr};            // Pointer to first ideal voltage source
    _drivers = 0;
    double G = 0.0;
    for (Pin * p : _pins) {
        // Skip non-driving Pins
        if (p->isDrvNC()) continue;
        // Add up Rg
//        std::cout << "** _Rdrv: " << p->_Rdrv << std::endl;
        G += 1 / p->_Rdrv;
        // Check for voltage source
        if (p->isDrvVS()) {
            if (!ivs_ptr) {           // Ideal Voltage source
                ivs_ptr = p;          // Store pointer to first VS
                continue;
            } else {
                if (_enable_sc_exceptions && (p->_Udrv != ivs_ptr->_Udrv)) {     // Did we find a different voltage source?
                    shortCircuitException e(this);
                    throw e;
                }
            }
        } else {
            _drivers++;
        }
    }

    double Rg = 1 / G;
    double U = 0;
    if (ivs_ptr) {
        U = ivs_ptr->_Udrv;
    } else {
        if (_drivers) {
            U  = zero( [&](double U) -> double { return Isum(U); } );
            //            std::cout << "**** Calculate new U for " << getName() << ": " << u << "V" << std::endl;
        }
    }

    // Check if the State of the Net has changed,
    // and update all Pins in the Net in this case
    if (_U != U || _Rg != Rg) {
        _U    = U;
        _Rg   = Rg;
        for (Pin * p : _pins) {
            p->update(usp);
        }
    }

}

double Net::Isum(double U, const Pin * p) const {
    double res = 0;
    for (Pin * pin : _pins) {
        if (pin != p && pin->_Idrv) {
            res += pin->_Idrv(U);
        }
    }
    return res;
}

double Net::IsumwVS(double U) const {
    double res = 0;
    for (Pin * pin : _pins) {
        if (pin->isDrvNC()) continue;
        if (pin->isDrvVS()) continue;
        if (pin->_Idrv) {
            res += pin->_Idrv(U);
        }
    }
    return res;
}


double Net::Rw(const Pin * p) const {
//    std::cout << std::endl << "Rw on" << p->getName() << std::endl;
//    return _R;
    if (isNC()) return INF;
//    if (isVS() && !p->isDrvVS()) return 0;

    double G = 0;
    for (Pin * pin : _pins) {
        if (pin != p) {
//            std::cout << "Adding " << p->getName() << std::endl;
            if (pin->isDrvNC()) continue;
            if (pin->isDrvVS()) return 0;
            G += 1/pin->_Rdrv;
        } else {
//            std::cout << "Skipping " << p->getName() << std::endl;
        }
    }
    return 1/G;
}

double Net::RwVS() const {
    if (isNC()) return INF;
    double G = 0;
    for (Pin * pin : _pins) {
        if (pin->isDrvNC()) continue;
        if (pin->isDrvVS()) continue;
        G += 1/pin->_Rdrv;
    }
    return 1/G;
}

std::ostream & operator << (std::ostream & os, const Net * net)
{
    os << "Net " << net->getName();
    if (net->isNC()) os << " NC ";
    if (net->isVS()) os << " VS ";
    os << "[" << net->U     << " V, "
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
