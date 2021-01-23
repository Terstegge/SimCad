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
// Low-level implementation of a inhibit gate.
// p[1]...p[N-1] are signal inputs (AND gate).
// p[N] is enable (active low).
//
#ifndef INCLUDE_INH_H_
#define INCLUDE_INH_H_

#include "Gate.h"

template<int N>
class INH : public Gate<N> {
public:

    INH(const std::string & name) : Gate<N>(name) {
    }

    void update(NetSet * nets) override {
        bool res = !(bool)this->p[N];
        for(int i=1; i < N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        this->OUT.setDrvBool(res, nets);
    }
};

#endif // INCLUDE_INH_H_
