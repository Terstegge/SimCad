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
#ifndef _INCLUDE_BUF_H_
#define _INCLUDE_BUF_H_

#include "Gate.h"

class BUF : public Gate<1> {
public:

    BUF(const std::string & name) : Gate<1>(name) {
    }

    void calculate(NetSet * nset) override {
        bool res = (bool)this->p[1];
        this->setOUTbool(res, nset);
    }
};

#endif // _INCLUDE_BUF_H_
