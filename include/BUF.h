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
// Buffer.
//
#ifndef _BUF_H_
#define _BUF_H_

#include "GATE.h"

class BUF : public GATE<1> {
public:

    BUF(const string & name) : GATE<1>(name) { }

    State calculate() override
    {
        bool res = (bool)this->p[1];
        return toState(res);
    }

};

#endif // _BUF_H_
