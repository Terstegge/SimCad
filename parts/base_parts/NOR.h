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
// Low-level implementation of a NOR gate
// with N inputs (p[1]...p[N]).
//
#ifndef _INCLUDE_NOR_H_
#define _INCLUDE_NOR_H_

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

#endif // _INCLUDE_NOR_H_
