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
#ifndef _PARTS_BASE_PARTS_BJT_PNP_H_
#define _PARTS_BASE_PARTS_BJT_PNP_H_

#include "Pin.h"
#include "TwoPole.h"
#include "Narray.h"

#include <iostream>
#include <string>
#include <cmath>

#include "DIODE.h"

class BJT_PNP : public Named {
public:

    enum class PinOrder { CBE, EBC };

    Narray<Pin, 4> p;
    Pin *    B;
    Pin *    E;
    Pin *    C;

    BJT_PNP(const std::string & name, PinOrder order)
    : Named(name), NAME(p),
      NAME(_Deb, Ueb_f), NAME(_Pec, this)
    {
        B = &p[2];
        switch(order) {
            case PinOrder::CBE:
                C = &p[1];
                E = &p[3];
                break;
            case PinOrder::EBC:
                E = &p[1];
                C = &p[3];
                break;
        }

        _Iec_sat = 0;

        // Set up the Basis-Emitter Diode
        B->connect_to(_Deb.C);
        E->connect_to(_Deb.A);
        // Setup Collector-Emitter Resistor
        C->connect_to(_Pec.p[1]);
        E->connect_to(_Pec.p[2]);

        // Attach Basis-handler
        B->attach( [this](NetSet * nset) {
            _Iec_sat  = _Deb.A.I() * beta;
            _Pec.update(nset);
        });
    }

private:
    // Internal class to model the
    // Collector-Emitter path as a TwoPole
    class CEpath : public TwoPole {

    public:
        CEpath(const std::string & name, BJT_PNP * owner) : TwoPole(name), o(owner) {
        }
    private:
        double Rchar(double U) {
            if (U == 0.0) {
                return o->Uearly / o->_Iec_sat * (1 + exp(50 * 0.15))  / (1 + 50 * o->Uearly);
            } else {
                return U / Ichar(U);
            }
        }

        double Ichar(double U) {
            return o->_Iec_sat * (U / o->Uearly + 1) / (1 + exp(-50 * (U - 0.15)));
        }
        BJT_PNP   *o;
    };

    // Configuration items
    const double Ueb_f  = 0.725;
    const double beta   = 200;
    const double Uearly = 100;

    DIODE   _Deb;
    CEpath  _Pec;

    // Calculated values
    double _Iec_sat;
};

#endif // _PARTS_BASE_PARTS_BJT_PNP_H_
