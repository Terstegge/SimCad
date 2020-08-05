#ifndef _BUF_H_
#define _BUF_H_

#include "GATE.h"

class BUF : public GATE<1> {
public:

    BUF(const string & name) : GATE<1>(name) { }

    State calculate() override
    {
        bool res = (bool)this->p[1];
        return toState(res);
    }

};

#endif // _BUF_H_
