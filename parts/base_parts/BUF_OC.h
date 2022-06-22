///////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
///////////////////////////////////////////////
//
// Low-level implementation of a non-inverting
// Buffer with open collector output.
//
#ifndef _PARTS_BASE_PARTS_BUF_OC_H_
#define _PARTS_BASE_PARTS_BUF_OC_H_

#include "Gate.h"

class BUF_OC : public Gate<1> {
public:

    BUF_OC(const std::string & name) : Gate<1>(name) {
    }

    void calculate(NetSet * nset) override {
        bool res = (bool)this->p[1];
        if (res) this->setOUTnc(nset);
        else     this->setOUTbool(false, nset);
    }
};

#endif // _PARTS_BASE_PARTS_BUF_OC_H_
