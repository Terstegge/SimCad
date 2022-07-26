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
#ifndef _INCLUDE_BC107_H_
#define _INCLUDE_BC107_H_

#include "Pin.h"
#include "TwoPole.h"
#include "Narray.h"

#include <iostream>
#include <string>
#include <cmath>

#include "DIODE.h"

class BC107 : public Named {
public:
    Narray<Pin, 4> p;
    Pin &    B;
    Pin &    E;
    Pin &    C;

    BC107(const std::string & name)
    : Named(name), NAME(p),
      B(p[2]), E(p[1]), C(p[3]),
      NAME(_Dbe, Ube_f), NAME(_Pce, this)
    {
        _Ice_sat = 0;

        // Setup the Basis-Emitter Diode
        B.connect_to(_Dbe.A);
        E.connect_to(_Dbe.C);
        // Setup Collector-Emitter Resistor
        C.connect_to(_Pce.p[2]);
        E.connect_to(_Pce.p[1]);

        // Attach Basis-handler
        B.attach( [this](NetSet * nset) {
            _Ice_sat  = _Dbe.A.I() * beta;
            _Pce.update(nset);
        });
    }

private:
    // Internal class to model the
    // Collector-Emitter path as a TwoPole
    class CEpath : public TwoPole {

    public:
        CEpath(const std::string & name, BC107 * owner) : TwoPole(name), o(owner) {
        }
    private:
        double Rchar(double U) {
            if (U == 0.0) {
                return o->Uearly / o->_Ice_sat * (1 + exp(50 * 0.15))  / (1 + 50 * o->Uearly);
            } else {
                return U / Ichar(U);
            }
        }

        double Ichar(double U) {
            return o->_Ice_sat * (U / o->Uearly + 1) / (1 + exp(-50 * (U - 0.15)));
        }
        BC107   *o;
    };

    // Configuration items
    const double Ube_f  = 0.725;
    const double beta   = 200;
    const double Uearly = 100;

    DIODE   _Dbe;
    CEpath  _Pce;

    // Calculated values
    double _Ice_sat;
};

#endif // _INCLUDE_BC107_H_
