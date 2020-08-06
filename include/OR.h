#ifndef _OR_H_
#define _OR_H_

#include "GATE.h"

template<int N>
class OR : public GATE<N> {
public:

    OR(const string & name) : GATE<N>(name) { }

    State calculate() override
    {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res |= (bool)this->p[i];
            if (res) break;
        }
        return toState(res);
    }

};

#endif // _OR_H_
