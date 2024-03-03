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
#ifndef _INCLUDE_WIRE_H_
#define _INCLUDE_WIRE_H_

#include <functional>
#include <memory>
#include <cmath>

#include "Pin.h"
#include "Narray.h"

class Wire : public Named {
public:

    Narray<Pin, 3> p;    // TwoPole Pins, only p[1] and p[2] are used

    Wire(const std::string & name) : Named(name), NAME(p), _connected(false) {
        // Attach handlers
        p[1].attach([this](NetSet * nset) {
            if (_connected) {
                p[2]._Udrv = p[1].U();
                p[2]._Rdrv = p[1].getNet()->Rw(&p[1]);
                p[2]._Idrv = [&] (double U) -> double {
                    return p[1].getNet()->Isum(U, &p[1]);
                };
            } else {
                p[2]._Rdrv = INF;
                p[2]._Idrv = nullptr;
            }
            if (!p[1].isVS() && p[2].isVS()) {
                p[2].update(nset);
            } else {
                nset->insert(p[2].getNet());
            }
        });

        p[2].attach([this](NetSet * nset) {
            if (_connected) {
                p[1]._Udrv = p[2].U();
                p[1]._Rdrv = p[2].getNet()->Rw(&p[2]);
                p[1]._Idrv = [&] (double U) -> double {
                    return p[2].getNet()->Isum(U, &p[2]);
                };
            } else {
                p[1]._Rdrv = INF;
                p[1]._Idrv = nullptr;
            }
            if (p[1].isVS() && !p[2].isVS()) {
                p[1].update(nset);
            } else {
                nset->insert(p[1].getNet());
            }
        });
    }

    virtual ~Wire() {
    }

    void update() {
        NetSet set1, set2;
        p[1].update(&set1);
        p[2].update(&set1);
        while (set1.size()) {
            set2.clear();
            for (Net * net : set1) {
                net->update(&set2);
            }
            set1 = set2;
        }
    }

//private:
    bool    _connected;
};

#endif // _INCLUDE_WIRE_H_
