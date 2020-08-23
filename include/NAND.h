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
#ifndef INCLUDE_NAND_H_
#define INCLUDE_NAND_H_

#include "Gate.h"

template<int N>
class NAND : public Gate<N> {
public:

    NAND(const std::string & name) : Gate<N>(name) {
    }

    State calculate() override {
        bool res = true;
        for(int i=1; i <= N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        return !res;
    }
};

#endif // INCLUDE_NAND_H_
