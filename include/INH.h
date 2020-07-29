#ifndef _INH_H_
#define _INH_H_

#include "GATE.h"

template<int N>
class INH : public GATE<N> {
public:

    INH(const string & name) : GATE<N>(name) { }

    State calculate() override
    {
        bool res = true;
        for(int i=1; i < N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        res &= !(bool)this->p[N];
        return res;
    }

};

#endif // _NOR_H_
