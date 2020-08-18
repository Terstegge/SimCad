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
// Low-level implementation of a inverting
// Buffer.
//
#ifndef _INV_H_
#define _INV_H_

#include "Gate.h"

class INV : public Gate<1> {
public:

    INV(const string & name) : Gate<1>(name) { }

    State calculate() override
    {
        bool res = !(bool)this->p[1];
        return res;
    }

};

#endif // _EOR_H_
