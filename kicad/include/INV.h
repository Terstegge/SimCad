#ifndef _INV_H_
#define _INV_H_

#include "GATE.h"

class INV : public GATE<1> {
public:

    INV(const string & name) : GATE<1>(name) { }

    State calculate() override
    {
        return toState(!(bool)this->p[1]);
    }

};

#endif // _INV_H_
