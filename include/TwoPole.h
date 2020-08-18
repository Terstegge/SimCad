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
// resistors and diodes). Currently only the
// DC resistance is stored.
//
#ifndef INCLUDE_TWOPOLE_H_
#define INCLUDE_TWOPOLE_H_

#include "Part.h"
#include "Pin.h"
#include "Narray.h"

class TwoPole : public Part {
public:
    Narray<Pin, 3> p;
    float          TP_R;   // TwoPole DC resistance

    TwoPole(const string & name, float r)
    : Part(name), p(name+".p"), TP_R(r)
    {
        p[1].setPartPtr(this);
        p[2].setPartPtr(this);
    }

    Pin * other(Pin * pin) {
        return (pin == &p[1]) ? &p[2] : &p[1];
    }
};

#endif /* INCLUDE_TWOPOLE_H_ */
