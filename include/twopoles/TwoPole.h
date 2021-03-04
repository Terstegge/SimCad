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
// Base class for all kinds of two-poles (e.g.
// voltage/current sources or resistors and diodes).
//
#ifndef _INCLUDE_TWOPOLE_H_
#define _INCLUDE_TWOPOLE_H_

#include <functional>

#include "Pin.h"
#include "Narray.h"


class TwoPole : public Named {
public:
    // TwoPole Pins, only p[1] and p[2] are used
    Narray<Pin, 3> p;

    TwoPole(const std::string & name) : Named(name), NAME(p), _G(0) {

        // Attach handlers
        p[1].attach([this](ElementSet * esp) {
            p[2].setUd( p[1].Uw() ); // Alt: p[1].U();
            p[2].setId( p[1].Iw() );
            p1_callback();
            p[2].setGd( 1.0/(1.0/p[1].Gw() + 1.0/_G) ); // Alt: G;
            if (!p[1].isVS() && p[2].isVS()) {
                esp->insert(&p[2]);
            } else {
                esp->insert(p[2].getNetPtr());
            }
        });

        p[2].attach([this](ElementSet * esp) {
            p[1].setUd( p[2].Uw() ); // Alt: p[2].U();
            p[1].setId( p[2].Iw() );
            p2_callback();
            p[1].setGd( 1.0/(1.0/p[2].Gw() + 1.0/_G) ); // Alt: G;
            if (p[1].isVS() && !p[2].isVS()) {
                esp->insert(&p[1]);
            } else {
                esp->insert(p[1].getNetPtr());
            }
        });
    }

    virtual ~TwoPole() {
    }

    virtual void p1_callback()  { }
    virtual void p2_callback()  { }

    void update() {
        ElementSet nset1, nset2;
        p[1].update(&nset1);
        p[2].update(&nset1);
        while (nset1.size()) {
            nset2.clear();
            for (ElementPtr net : nset1) {
                net->update(&nset2);
            }
            nset1 = nset2;
        }
    }

protected:
    double _G;
};

#endif // _INCLUDE_TWOPOLE_H_
