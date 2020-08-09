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
#ifndef _INH_H_
#define _INH_H_

#include "GATE.h"

template<int N>
class INH : public GATE<N> {
public:

    INH(const string & name) : GATE<N>(name) { }

    State calculate() override
    {
        bool res = !(bool)this->p[N];
        for(int i=1; i < N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        return toState(res);
    }
};

#endif // _INH_H_
