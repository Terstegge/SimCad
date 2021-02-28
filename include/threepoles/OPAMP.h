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
#ifndef INCLUDE_GATES_OPAMP_H_
#define INCLUDE_GATES_OPAMP_H_

#include "Pin.h"
#include "Narray.h"

#include <iostream>
#include <string>
#include <cmath>

class OPAMP : public Named {
public:
    Narray<Pin, 6> p;
    Pin &    Iplus;
    Pin &    Iminus;
    Pin &    OUT;
    Pin &    Vplus;
    Pin &    Vminus;

    bool on;
    bool calc;

    double upper;
    double lower;

    OPAMP(const std::string & name)
        : Named(name), NAME(p),
          Iplus(p[1]), Iminus(p[2]), OUT(p[3]),
          Vplus(p[4]), Vminus(p[5]),
          on(false), calc(false), upper(0), lower(0)
    {
        // Set the part pointers
//        for (Pin & pin : p) {
//            pin.setPartPtr(this);
//        }
        // Attach power signals
        Vplus.attach( [this](ElementSet * esp) {
            on  = Vplus.isVS() && Vminus.isVS();
            if (on) {
                calculate(esp);
            } else {
                OUT.setDrvNC(esp);
            }
        });
        Vminus.attach( [this](ElementSet * esp) {
            on  = Vplus.isVS() && Vminus.isVS();
            if (on) {
                calculate(esp);
            } else {
                OUT.setDrvNC(esp);
            }
        });
        // Attach input signal handlers
        Iplus.attach([this](ElementSet * esp) {
            if (on) {
                calculate(esp);
            } else {
                OUT.setDrvNC(esp);
            }
        });
        Iminus.attach([this](ElementSet * esp) {
            if (on) {
                calculate(esp);
            } else {
                OUT.setDrvNC(esp);
            }
        });
    }

    void calculate(ElementSet * esp) {
        if (!calc) {
            calc = true;
            upper = Vplus.U();
            lower = Vminus.U();
            double diff = Iplus.U() - Iminus.U();
            diff *= 1e5;
            if (diff > Vplus.U())  diff = Vplus.U();
            if (diff < Vminus.U()) diff = Vminus.U();
            OUT = diff;
            calc = false;
        } else {
            // Recursion
            double diff = Iplus.U() - Iminus.U();
            if (fabs(diff) < EPS) return;
//            if (diff == 0) return;
            if (diff < 0.0) upper = OUT.Ud;
                else        lower = OUT.Ud;
            OUT = (upper + lower) / 2;
        }
    }

private:
    const double EPS = 1e-5;
};

#endif /* INCLUDE_GATES_OPAMP_H_ */
