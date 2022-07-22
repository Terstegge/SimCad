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
#ifndef _PARTS_PSPICE_OPAMP_H_
#define _PARTS_PSPICE_OPAMP_H_

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
        // Attach power signals
        Vplus.attach( [this](NetSet * nset) {
            on  = Vplus.isVS() && Vminus.isVS();
            if (on) {
                calculate(nset);
            } else {
                OUT.setDrvNC(nset);
            }
        });
        Vminus.attach( [this](NetSet * nset) {
            on  = Vplus.isVS() && Vminus.isVS();
            if (on) {
                calculate(nset);
            } else {
                OUT.setDrvNC(nset);
            }
        });
        // Attach input signal handlers
        Iplus.attach([this](NetSet * nset) {
            if (on) {
                calculate(nset);
            } else {
                OUT.setDrvNC(nset);
            }
        });
        Iminus.attach([this](NetSet * nset) {
            if (on) {
                calculate(nset);
            } else {
                OUT.setDrvNC(nset);
            }
        });
    }
    void calculate(NetSet * nset) {
        if (!calc) {
            calc = true;
            upper = Vplus.U();
            lower = Vminus.U();
            double diff = Iplus.U() - Iminus.U();
            diff *= 1e5;
            if (diff > Vplus.U())  diff = Vplus.U();
            if (diff < Vminus.U()) diff = Vminus.U();
            // Start a new update on the OUT pin
            OUT = diff;
            calc = false;
        } else {
            // Recursion
            double diff = Iplus.U() - Iminus.U();
            if (fabs(diff) < EPS) return;
//            if (diff == 0) return;
            if (diff < 0.0) upper = OUT.U();
                else        lower = OUT.U();
            OUT.setDrvVS((upper + lower) / 2, nset);
        }
    }
private:
    const double EPS = 1e-5;
};

#endif // _PARTS_PSPICE_OPAMP_H_
