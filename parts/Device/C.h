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
        _R = 0.01;
    }

    ~C() {
        stop();
    }

    void start() {
        if (!_running) {
            _running = true;
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

    double Ichar(double U) override {
        return (U - _U) /_R;
    }

private:
    const int dt_millis = 10;

    double  _cap;	// Capacity in F
    double  _Q;		// Current charge in As
    double  _U;		// Current voltage V
    double  _R;

    thread  _t;
    bool    _running;
};

#endif // _INCLUDE_C_H_
