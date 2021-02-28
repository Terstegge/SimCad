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
// three-state Buffer with enable input.
//
// p[1] is signal input
// p[2] is enable input (active high).
//
#ifndef INCLUDE_BUF_G_H_
#define INCLUDE_BUF_G_H_

#include "Gate.h"

class BUF_G : public Gate<2> {
public:
    Pin & G;

    BUF_G(const std::string & name) : Gate<2>(name), G(this->p[2]) {
    }

    void calculate(ElementSet * esp) override {
        bool res = (bool)this->p[1];
        G ? this->OUT.setDrvBool(res, esp)
          : this->OUT.setDrvNC(esp);
    }
};

#endif // INCLUDE_BUF_G_H_
