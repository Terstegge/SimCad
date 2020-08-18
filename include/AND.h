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
#ifndef _AND_H_
#define _AND_H_

#include "Gate.h"

template<int N>
class AND : public Gate<N> {
public:

    AND(const string & name) : Gate<N>(name) { }

    State calculate() override
    {
        bool res = true;
        for(int i=1; i <= N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        return res;
    }

};

#endif // _AND_H_
