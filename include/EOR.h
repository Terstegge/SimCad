#ifndef _EOR_H_
#define _EOR_H_

#include "GATE.h"

template<int N>
class EOR : public GATE<N> {
public:

    EOR(const string & name) : GATE<N>(name) { }

    State calculate() override
    {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res ^= (bool)this->p[i];
        }
        return toState(res);
    }

};

#endif // _EOR_H_
