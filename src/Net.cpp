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
#include <cassert>

bool Net::_enable_sc_exceptions = true;;

using entry = std::pair <Pin *, std::function<double(double)>>;

int Net::sgn(double v) {
    return (v > 0) - (v < 0);
}

double Net::zero(std::function<double(double)> f) {
    int k = 0;
    double low = -5.5;
    double high = 5.5;
    double f_high = f(high);
    double f_low  = f(low);
    if (f_high == 0.0 && f_low != 0.0) return high;
    if (f_high != 0.0 && f_low == 0.0) return low;
    if (f_high == 0.0 && f_low == 0.0) return (high-low)/2.0;
    if ( f(high) * f(low) >= 0.0) {
        std::cout << "*** error *** " << getName() << std::endl;
        for (double u = 0.0; u <= 5.0; u += 0.5) {
            std::cout << u << "V\t";
            std::cout << f(u) << "A\t";
            std::cout << std::endl;
        }
        //        return 0.0;
        //exit(1);
    }
    while ((high - low) > 1e-8) {
        double f_high = f(high);
        double f_low  = f(low);
        if (f_high == 0.0) return high;
        if (f_low  == 0.0) return low;
        double u = (high + low) / 2.0;
        if (sgn(f_high) == sgn(f(u)))
            high = u; else low = u;
        k++;
    }
    //    std::cout << "K: " << k << std::endl;
    return (high+low)/2.0;
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
                    short_circuit_exception e(this);
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

double Net::Isum(double U, Pin * p) const {
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

ostream & operator << (ostream & os, const Net * net)
{
    os << "Net " << net->getName();
    if (net->isNC()) os << " NC ";
    if (net->isVS()) os << " VS ";
    os << "[" << net->U     << " V, "
            << net->R()  << " Ohm]"
            << std::endl;
    for (Pin * p : net->_pins) {
        if (p->isDrvNC()) continue;
        os << "  driven by "
                << drive << (*p)
                << std::endl;
    }
    return os;
}
