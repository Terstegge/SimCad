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
// Low-level implementation of a non-inverting
// Buffer with enable input (active HIGH).
// p[1] is signal input
// p[2] is enable input
//
#ifndef _BUF_G_H_
#define _BUF_G_H_

#include "GATE.h"

class BUF_G : public GATE<2> {
public:
    Pin & G;

    BUF_G(const string & name) : GATE<2>(name), G(this->p[2]) { }

    State calculate() override
    {
        bool res = (bool)this->p[1];
        return G ? toState(res) : NC;
    }

};

#endif // _BUF_G_H_
