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
#ifndef INCLUDE_BUF_H_
#define INCLUDE_BUF_H_

#include "Gate.h"

class BUF : public Gate<1> {
public:

    BUF(const std::string & name) : Gate<1>(name) {
    }

    void calculate(ElementSet * esp) override {
        bool res = (bool)this->p[1];
        this->OUT.setDrvBool(res, esp);
    }
};

#endif // INCLUDE_BUF_H_
