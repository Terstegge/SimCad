/////////////////////////////////////////////////
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
/////////////////////////////////////////////////
//
// Low-level implementation of a non-inverting
// three-state Buffer with enable input.
//
// p[1] is signal input
// p[2] is enable input (active high).
//
#ifndef _PARTS_BASE_PARTS_BUF_G_H_
#define _PARTS_BASE_PARTS_BUF_G_H_

#include "Gate.h"

class BUF_G : public Gate<2> {
public:
    Pin & G;

    BUF_G(const std::string & name) : Gate<2>(name), G(this->p[2]) {
    }

    void calculate(NetSet * nset) override {
        bool res = (bool)this->p[1];
        G ? this->setOUTbool(res, nset)
          : this->setOUTnc(nset);
    }
};

#endif // _PARTS_BASE_PARTS_BUF_G_H_
