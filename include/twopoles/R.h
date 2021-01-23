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
// Low-level implementation of a resistor.
// The voltage of the changing net is propagated
// to the other side of the resistor, using the
// configured resistance.
//
#ifndef INCLUDE_R_H_
#define INCLUDE_R_H_

#include "TwoPole.h"

class R : public TwoPole {

public:
    R(const std::string & name, float r) : TwoPole(name) {
        this->G = 1.0/r;
    }
};

#endif // INCLUDE_R_H_
