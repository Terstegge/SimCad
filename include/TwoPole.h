///////////////////////////////////////////////
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//  A simulation package for digital circuits
//  (c) 2020  A. Terstegge
///////////////////////////////////////////////
// Base class for all kinds of two-poles (e.g.
// voltage/current sources or resistors and diodes).
#ifndef _INCLUDE_TWOPOLE_H_
#define _INCLUDE_TWOPOLE_H_
#include <functional>
#include <memory>
#include "Pin.h"
#include "Narray.h"

class TwoPole : public Named {
public:
	// TwoPole Pins, only p[1] and p[2] are used
    Narray<Pin, 3> p;
    TwoPole(const std::string & name) : Named(name), NAME(p) {
        // Attach handlers
        p[1].attach([this](NetSet * nset) {
            p[2]._Idrv = [&] (double U) -> double {
                return Ichar(U - p[1].U());
            };
            if (!p[1].isVS() && p[2].isVS()) {
                p[2].update(nset);
            } else {
                nset->insert(p[2].getNet());
            }
        });
        p[2].attach([this](NetSet * nset) {
            p[1]._Idrv = [&] (double U) -> double {
                return -Ichar(p[2].U() - U);
            };
            if (p[1].isVS() && !p[2].isVS()) {
                p[1].update(nset);
            } else {
                nset->insert(p[1].getNet());
            }
        });
    }

    virtual ~TwoPole() {
    }

    // The I(U) characteristic of the twopole. The voltage
    // U is calculated as U = p[2].U - p[1].U. This is important
    // for parts with non-linar behaviour.
    virtual double Ichar(double) = 0;

    void update() {
        NetSet set1, set2;
        p[1].update(&set1);
        p[2].update(&set1);
        while (set1.size()) {
            set2.clear();
            for (Net * net : set1) {
            	net->_mutex.lock();
                net->update(&set2);
                net->_mutex.unlock();
            }
            set1 = set2;
        }
    }
};

#endif // _INCLUDE_TWOPOLE_H_
