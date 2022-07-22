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
// Low-level implementation of a inhibit gate.
// p[1]...p[N-1] are signal inputs (AND gate).
// p[N] is enable (active low).
//
#ifndef _PARTS_BASE_PARTS_INH_H_
#define _PARTS_BASE_PARTS_INH_H_

#include "Gate.h"

template<int N>
class INH : public Gate<N> {
public:

    INH(const std::string & name) : Gate<N>(name) {
    }

    void calculate(NetSet * nset) override {
        bool res = !(bool)this->p[N];
        for(int i=1; i < N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        this->setOUTbool(res, nset);
    }
};

#endif // _PARTS_BASE_PARTS_INH_H_
