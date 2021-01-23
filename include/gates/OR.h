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
// Low-level implementation of an OR gate
// with N inputs (p[1]...p[N]).
//
#ifndef INCLUDE_OR_H_
#define INCLUDE_OR_H_

#include "Gate.h"

template<int N>
class OR : public Gate<N> {
public:

    OR(const std::string & name) : Gate<N>(name) {
    }

    void update(NetSet * nets) override {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res |= (bool)this->p[i];
            if (res) break;
        }
        this->OUT.setDrvBool(res, nets);
    }
};

#endif // INCLUDE_OR_H_
