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
// Low-level implementation of a EOR (XOR) gate
// with N inputs (p[1]...p[N]). For more than
// 2 inputs, the output is a odd parity function.
//
#ifndef _PARTS_BASE_PARTS_EOR_H_
#define _PARTS_BASE_PARTS_EOR_H_

#include "Gate.h"

template<int N>
class EOR : public Gate<N> {
public:

    EOR(const std::string & name) : Gate<N>(name) {
    }

    void calculate(NetSet * nset) override {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res ^= (bool)this->p[i];
        }
        this->setOUTbool(res, nset);
    }
};

#endif // _PARTS_BASE_PARTS_EOR_H_
