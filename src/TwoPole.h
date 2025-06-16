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
// Base class for various kinds of two-poles, e.g.
//  - resistors
//  - diodes
//  - (ideal) current/voltage sources
//  - ...
//
#ifndef _INCLUDE_TWOPOLE_H_
#define _INCLUDE_TWOPOLE_H_

#include <functional>
#include <memory>
#include <cmath>

#include "Pin.h"
#include "Narray.h"

class TwoPole : public Named {
public:

    Narray<Pin, 3> p;    // TwoPole Pins, only p[1] and p[2] are used
    double _Usrc;        // Voltage offset if the TwoPole is a voltage source
    double _Isrc;        // Current offset if the TwoPole is a current source

    TwoPole(const std::string & name) : Named(name), NAME(p), _Usrc(0), _Isrc(0) {
        // Attach handlers
        p[1].attach([this](NetSet * nset) {
            double R = Rchar(p[2].U() - p[1].U());
            if (R == 0) {
                p[2]._Udrv = p[1].U() + _Usrc;
                p[2]._Rdrv = p[1].getNet()->Rw(&p[1]);
                p[2]._Idrv = [&] (double U) -> double {
                    return p[1].getNet()->Isum(U + _Usrc, &p[1]);
                };
            } else if (R == INF) {
                p[2]._Rdrv = INF;
                p[2]._Idrv = nullptr;
                if (_Isrc != 0.0) {
                    p[2]._Idrv = [&](double) {
                        return _Isrc;
                    };
                }
            } else {
                p[2]._Rdrv = p[1].getNet()->Rw(&p[1]) + R;
                p[2]._Idrv = [&] (double U) -> double {
                    return Ichar(U - p[1].U());
                };
            }
            if (!p[1].isVS() && p[2].isVS()) {
                p[2].update(nset);
            } else {
                nset->insert(p[2].getNet());
            }
        });

        p[2].attach([this](NetSet * nset) {
            double R = Rchar(p[2].U() - p[1].U());
            if (R == 0) {
                p[1]._Udrv = p[2].U() - _Usrc;
                p[1]._Rdrv = p[2].getNet()->Rw(&p[2]);
                p[1]._Idrv = [&] (double U) -> double {
                    return p[2].getNet()->Isum(U + _Usrc, &p[2]);
                };
            } else if (R == INF) {
                p[1]._Rdrv = INF;
                p[1]._Idrv = nullptr;
                if (_Isrc != 0.0) {
                    p[1]._Idrv = [&](double) {
                        return -_Isrc;
                    };
                }
            } else {
                p[1]._Rdrv = p[2].getNet()->Rw(&p[2]) + R;
                p[1]._Idrv = [&] (double U) -> double {
                    return -Ichar(p[2].U() - U);
                };
            }
            if (p[1].isVS() && !p[2].isVS()) {
                p[1].update(nset);
            } else {
                nset->insert(p[1].getNet());
            }
        });
    }

    virtual ~TwoPole() = default;

    // The R(U) characteristic of the TwoPole. Normally this
    // characteristic can be calculated as U / Ichar(U), but
    // the case U==0, Ichar(0)==0 has to get special attention
    // to not generate a NAN result or to calculate the correct
    // R value at this point. Default is INF (Pin is not connected).
    virtual double Rchar(double U) {
        return INF;
    }

    // The I(U) characteristic of the TwoPole. The voltage
    // U is calculated as U = p[2].U - p[1].U. This is important
    // for parts with non-linar behavior. Default is 0, so no
    // current at all voltages (Pin is not connected).
    virtual double Ichar(double U) {
        return 0;
    }

    void update(NetSet * nset = nullptr) {
        if (nset) {
            p[1].update(nset);
            p[2].update(nset);
        } else {
            NetSet set1, set2;
            p[1].update(&set1);
            p[2].update(&set1);
            while (!set1.empty()) {
                set2.clear();
                for (Net * net : set1) {
                    net->update(&set2);
                }
                set1 = set2;
            }
        }
    }
};

#endif // _INCLUDE_TWOPOLE_H_
