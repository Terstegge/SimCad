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
// Implementation of a nonpolar capacitor.
//
#include <cmath>
#include "C.h"

// static C-thread stuff
std::vector<C *> C::_capacitors;
std::mutex       C::_capacitors_mutex;
thread           C::_thread;
bool             C::_running  = false;
const int        C::dt_millis = 10;


C::C(const std::string &name, double c) : TwoPole(name) {
    // Initialize values
    _cap = c;
    _Q   = 0;
    _U   = 0;
    _R   = (double)dt_millis / (_cap * 1000);

    // Add this C to list
    _capacitors_mutex.lock();
    _capacitors.push_back(this);
    _capacitors_mutex.unlock();
}

void C::stop() {
    if (_running) {
        _running = false;
        _thread.join();
    }
}

double C::Ichar(double U) {
    return (U - _U) / _R;
}

double C::Rchar(double U) {
    if (U == 0 && _U == 0) {
        return _R;
    } else {
        return U / Ichar(U);
    }
}


void C::setCapacity(double cap) {
    _cap = cap;
    _Q = 0;
    _U = 0;
    _R   = (double)dt_millis / (_cap * 1000);
}

void C::start() {
    if (!_running) {
        _running = true;
        _thread = thread([]() {
            auto startTime = system_clock::now();
            while (_running) {
                // Wait for another dt_millis
                startTime += milliseconds(dt_millis);
                sleep_until(startTime);
                // Update the charge of the capacitors
                _capacitors_mutex.lock();
                for (auto c : _capacitors) {
                    // Get current through capacitor
                    double I = c->p[2].I();
                    double Iabs = fabs(I);
                    // Check for very small currents
                    if (Iabs < 1E-6) continue;
                    // Sum up electric charge
                    c->_Q += I * (double)dt_millis;
                    c->_U = c->_Q / (c->_cap * 1000);
                    // Update NETs
                    c->update();
                }
                _capacitors_mutex.unlock();
            }
        });
    }
}
