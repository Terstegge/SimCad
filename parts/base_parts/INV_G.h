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
// Low-level implementation of an inverting
// three-state Buffer with enable input.
//
// p[1] is signal input
// p[2] is enable input (active high)
//
#ifndef _INCLUDE_INV_G_H_
#define _INCLUDE_INV_G_H_

#include "Gate.h"

class INV_G : public Gate<2> {
public:
    Pin & G;

    INV_G(const std::string & name) : Gate<2>(name), G(this->p[2]) {
    }

    void calculate(NetSet * nset) override {
        bool res = !(bool)this->p[1];
        G ? this->setOUTbool(res, nset)
          : this->setOUTnc(nset);
    }
};

#endif // _INCLUDE_INV_G_H_
