#ifndef _AND_H_
#define _AND_H_

#include "GATE.h"

template<int N>
class AND : public GATE<N> {
public:

    AND(const string & name) : GATE<N>(name) { }

    State calculate() override
    {
        bool res = true;
        for(int i=1; i <= N; ++i) {
            res &= (bool)this->p[i];
            if (!res) break;
        }
        return toState(res);
    }

};

#endif // _AND_H_
