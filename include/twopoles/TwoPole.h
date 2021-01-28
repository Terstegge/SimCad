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

#include "Part.h"
#include "Pin.h"
#include "Narray.h"


class TwoPole : public Part {
public:
    // TwoPole Pins, only p[1] and p[2] are used
    Narray<Pin, 3> p;

    TwoPole(const std::string & name) : Part(name), NAME(p), _G(0) {
        // Set the part pointers
        p[1].setPartPtr(this);
        p[2].setPartPtr(this);

        // Attach handlers
        p[1].attach([this](NetSet * nets) {

            p[2].Ud = p[1].Uw(); // Alt: p[1].U();
            p[2].Id = p[1].Gw() ? 0.0 : p[1].getNetPtr()->Id;
            p1_callback();
            p[2].Gd = 1.0/(1.0/p[1].Gw() + 1.0/_G); // Alt: G;
            NetPtr n = p[2].getNetPtr();
            if (n) nets->insert(n);
        });

        p[2].attach([this](NetSet * nets) {

            p[1].Ud = p[2].Uw(); // Alt: p[2].U();
            p[1].Id = p[2].Gw() ? 0.0 : p[2].getNetPtr()->Id;
            p2_callback();
            p[1].Gd = 1.0/(1.0/p[2].Gw() + 1.0/_G); // Alt: G;
            NetPtr n = p[1].getNetPtr();
            if (n) nets->insert(n);
        });
    }

    virtual ~TwoPole() {
    }

    virtual void p1_callback()  { }
    virtual void p2_callback()  { }

    void setG(float g) {
        _G = g;
    }

private:
    float _G;
};

#endif // _INCLUDE_TWOPOLE_H_
