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
// Low-level implementation of a EOR (XOR) gate
// with N inputs (p[1]...p[N]).
//
#ifndef INCLUDE_EOR_H_
#define INCLUDE_EOR_H_

#include "Gate.h"

template<int N>
class EOR : public Gate<N> {
public:

    EOR(const std::string & name) : Gate<N>(name) {
    }

    void calculate(ElementSet * esp) override {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res ^= (bool)this->p[i];
        }
        this->OUT.setDrvBool(res, esp);
    }
};

#endif // INCLUDE_EOR_H_
