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
