///////////////////////////////////////////////
//
//  This file is part of
//     ___  ____  __  __  ___    __    ____
//    / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//    \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//    (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation package for electronic circuits
//
//  (c) Andreas Terstegge
//
///////////////////////////////////////////////
//
// Implementation of a nonpolar capacitor.
//
#ifndef _INCLUDE_C_H_
#define _INCLUDE_C_H_

#include "TwoPole.h"
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

using std::thread;
using namespace std::chrono;
using namespace std::this_thread;

class C: public TwoPole {
public:
    C(const std::string &name, double c);
    //virtual ~C();

    double Ichar(double U) override;
    double Rchar(double U) override;

    void setCapacity(double cap);

    static void start();
    static void stop();

private:
    double _cap; // Capacity in F
    double _Q;   // Current charge in mAs
    double _U;   // Current voltage V
    double _R;

    static const int dt_millis;

    // C-thread stuff
    static std::vector<C *> _capacitors;
    static std::mutex       _capacitors_mutex;
    static thread           _thread;
    static bool             _running;

};

#endif // _INCLUDE_C_H_


//
//
//void start() {
//    if (!_running) {
//        _running = true;
//        //            _R = 0.01;
//        update();
//        _t = thread([this]() {
//            auto now = system_clock::now();
//            while (_running) {
//                // Add I * delta_t to charge
//                _Q += p[2].I() * (double) dt_millis;
//                // Calculate new voltage
//                _U = _Q / (_cap * 1000);
//                // Update the connected Nets
//                update();
//                // Wait for another delta_t
//                now += milliseconds(dt_millis);
//                sleep_until(now);
//            }
//        });
//    }
//}
//
//void stop() {
//    if (_running) {
//        _running = false;
//        _t.join();
//    }
//}
