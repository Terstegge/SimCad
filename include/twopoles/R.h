///////////////////////////////////////////////
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//  A simulation package for digital circuits
//  (c) 2020  A. Terstegge
///////////////////////////////////////////////
// Implementation of a resistor.
#ifndef _INCLUDE_R_H_
#define _INCLUDE_R_H_

#include "TwoPole.h"

class R : public TwoPole {
public:
    R(const std::string & name, double r) : TwoPole(name), _R(r) {
    }

    double Ichar(double U) override {
        return U /_R;
    }

    double _R;
};
#endif // _INCLUDE_R_H_
