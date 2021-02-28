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
// Low-level implementation of an AND gate
// with N inputs (p[1]...p[N]).
//
#ifndef INCLUDE_AND_H_
#define INCLUDE_AND_H_

#include "Gate.h"

template<int N>
class AND : public Gate<N> {
public:

    AND(const std::string & name) : Gate<N>(name) {
    }

    void calculate(ElementSet * esp) override {
        bool res = true;
        for(int i=1; i <= N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        this->OUT.setDrvBool(res, esp);
    }
};

#endif // INCLUDE_AND_H_
