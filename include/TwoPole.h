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
        p[1].attach([this](NetSet * usp) {
            if (p[1].isVS()) {
                p[2]._Idrv = [&] (double U) -> double {
                    return Ichar(U - p[1].U());
                };
            } else {
                p[2]._Idrv =  [&] (double U) -> double {
//                    return Ichar()(U - p[1].U());
                    Net * net = p[1].getNet();
                    return 1.0 / (1.0/net->Isum(U, &p[1])
                                + 1.0/Ichar(U - p[1]._Uw) );
                };
            }
            if (!p[1].isVS() && p[2].isVS()) {
                p[2].update(usp);
            } else {
                usp->insert(p[2].getNet());
            }
        });
        p[2].attach([this](NetSet * usp) {
            if (p[2].isVS()) {
                p[1]._Idrv = [&] (double U) -> double {
                    return Ichar(U - p[2].U());
                };
            } else {
                p[1]._Idrv = [&] (double U) -> double {
//                    return characteristic()(U - p[2].U());
                    Net * net = p[2].getNet();
                    return 1.0 / (1.0/net->Isum(U, &p[2])
                                + 1.0/Ichar(U - p[2]._Uw) );
                };
            }
            if (p[1].isVS() && !p[2].isVS()) {
                p[1].update(usp);
            } else {
                usp->insert(p[1].getNet());
            }
        });
    }

    virtual ~TwoPole() {
    }

    virtual double Ichar(double) = 0;

    void update() {
        int round = 0;
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
};

#endif // _INCLUDE_TWOPOLE_H_