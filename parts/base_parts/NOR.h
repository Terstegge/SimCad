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
// Low-level implementation of a NOR gate
// with N inputs (p[1]...p[N]).
//
#ifndef _PARTS_BASE_PARTS_NOR_H_
#define _PARTS_BASE_PARTS_NOR_H_

#include "Gate.h"

template<int N>
class NOR : public Gate<N> {
public:

    NOR(const std::string & name) : Gate<N>(name) {
    }

    void calculate(NetSet * nset) override {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res |= (bool)this->p[i];
            if (res) break;
        }
        this->setOUTbool(!res, nset);
    }
};

#endif // _PARTS_BASE_PARTS_NOR_H_
