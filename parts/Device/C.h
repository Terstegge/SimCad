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
// Implementation of a resistor.
//
#ifndef _INCLUDE_C_H_
#define _INCLUDE_C_H_

#include "TwoPole.h"
#include <thread>
#include <chrono>

using std::thread;
using namespace std::chrono;
using namespace std::this_thread;

class C : public TwoPole {
public:
    C(const std::string & name, double c) : TwoPole(name), _cap(c), _Q(0), _U(0), _running(false) {
        _G = 0;
    }

    ~C() {
        stop();
    }

    void start() {
        if (!_running) {
            _running = true;
            _G = 100;
            update();
            _t = thread([this]() {
                auto now = system_clock::now();
            	while(_running) {
            		// Add I * delta_t to charge
            		_Q += p[2].I() * (double)dt_millis;
            		// Calculate new voltage
            		_U  = _Q / (_cap * 1000);
            		// Update the connected Nets
            		update();
            		// Wait for another delta_t
            		now += milliseconds( dt_millis );
                    sleep_until(now);
                }
            });
        }
    }

    void stop() {
        if (_running) {
            _running = false;
            _t.join();
        }
    }

    void p1_callback() override {
        p[2].setUd( p[2].Ud + _U);
    }
    void p2_callback() override {
        p[1].setUd( p[1].Ud - _U);
    }

private:
    const int dt_millis = 10;

    double  _cap;	// Capacity in F
    double  _Q;		// Current charge in As
    double  _U;		// Current voltage V

    thread  _t;
    bool    _running;
};

#endif // _INCLUDE_C_H_
