#ifndef _NOR_H_
#define _NOR_H_

#include "GATE.h"

template<int N>
class NOR : public GATE<N> {
public:

    NOR(const string & name) : GATE<N>(name) { }

    State calculate() override
    {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res |= (bool)this->p[i];
            if (res) break;
        }
        return toState(!res);
    }

};

#endif // _NOR_H_
