#ifndef _BUF_H_
#define _BUF_H_

#include "GATE.h"

class BUF : public GATE<1> {
public:

    BUF(const string & name) : GATE<1>(name) { }

    State calculate() override
    {
        return this->p[1];
    }

};

#endif // _BUF_H_
