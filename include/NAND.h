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
// Low-level implementation of a NAND gate
// with N inputs (p[1]...p[N]).
//
#ifndef _NAND_H_
#define _NAND_H_

#include "GATE.h"

template<int N>
class NAND : public GATE<N> {
public:

    NAND(const string & name) : GATE<N>(name) { }

    State calculate() override
    {
        bool res = true;
        for(int i=1; i <= N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        return toState(!res);
    }

};

#endif // _NAND_H_
