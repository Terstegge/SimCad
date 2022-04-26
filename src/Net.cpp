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

using entry = std::pair <Pin *, std::function<double(double)>>;

int Net::sgn(double v) {
  return (v > 0) - (v < 0);
}

double Net::zero(std::function<double(double)> f) {
    int k = 0;
    double low = 0.0;
    double high = 5.0;
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

void Net::update(NetSet * usp) {
	//    std:: cout << "update " << getName() << std::endl;
	Pin * ivs_ptr {nullptr};            // Pointer to first ideal voltage source
	bool isnc = true;
	_drivers = 0;
	for (Pin * p : _pins) {
		// Skip non-driving Pins
		if (p->isDrvNC()) continue;
		// Check for voltage source
		if (p->isDrvVS()) {
			isnc = false;
			if (!ivs_ptr) {           // Ideal Voltage source
				ivs_ptr = p;          // Store pointer to first VS
				continue;
			} else {
				if (p->_Uvs != ivs_ptr->_Uvs) {     // Did we find a different voltage source?
					short_circuit_exception e(this);
					throw e;
				}
			}
		} else {
			isnc = false;
			_drivers++;
		}
	}
	if (!ivs_ptr  && _drivers) {
		for (Pin * p : _pins) {
			double ud = zero( [&](double U) -> double { return Isum(U, p); } );
			if (p->_Uw != ud) {
				p->_Uw = ud;
				p->update(usp);
			}
		}
	}

	double u {0};
	bool   vs{false};
	if (ivs_ptr) {
		u = ivs_ptr->_Uvs;
		vs = true;
	} else {
		if (_drivers) {
			u  = zero( [&](double U) -> double { return Isum(U); } );
			//            std::cout << "**** Calculate new U for " << getName() << ": " << u << "V" << std::endl;
		}
		vs = false;
	}
	// Check if the State of the Net has changed
	if (_U != u || _isVS != vs || _isNC != isnc) {
		//        if (getName().find("__R") != std::string::npos)
		//            std::cout << getName() << " U:" << u << "V" << std::endl;
		_U    = u;
		_isVS = vs;
		_isNC = isnc;
		for (Pin * p : _pins) {
			//            std::cout << "--------- Calling update on " << p->getName() << std::endl;
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

ostream & operator << (ostream & os, const Net * net)
{
    os << "Net " << net->getName();
    if (net->_isNC) os << " NC ";
    if (net->_isVS) os << " VS ";
    os << "[" << net->U     << " V, "
              << net->Rd()  << " Ohm]"
              << std::endl;
    for (Pin * p : net->_pins) {
        if (p->isDrvNC()) continue;
        os << "  driven by "
           << drive << (*p)
           << std::endl;
    }
    return os;
}
