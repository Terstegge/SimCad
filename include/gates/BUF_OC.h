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
#ifndef INCLUDE_BUF_OC_H_
#define INCLUDE_BUF_OC_H_

#include "Gate.h"

class BUF_OC : public Gate<1> {
public:

    BUF_OC(const std::string & name) : Gate<1>(name) {
    }

    void update(NetSet * nets) override {
        bool res = (bool)this->p[1];
        if (res) this->OUT.setDrvNC(nets);
        else     this->OUT.setDrvBool(false, nets);
    }
};

#endif // INCLUDE_BUF_OC_H_
