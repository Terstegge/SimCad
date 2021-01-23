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
#ifndef INCLUDE_INV_H_
#define INCLUDE_INV_H_

#include "Gate.h"

class INV : public Gate<1> {
public:

    INV(const std::string & name) : Gate<1>(name) {
    }

    void update(NetSet * nets) override {
        bool res = !(bool)this->p[1];
        this->OUT.setDrvBool(res, nets);
    }
};

#endif // INCLUDE_INV_H_
