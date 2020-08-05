#ifndef _BUF_G_H_
#define _BUF_G_H_

#include "GATE.h"

class BUF_G : public GATE<2> {
public:

    Pin & G;

    BUF_G(const string & name) : GATE<2>(name), G(this->p[2]) { }

    State calculate() override
    {
        bool res = (bool)this->p[1];
        return G ? toState(res) : NC;
    }

};

#endif // _BUF_G_H_
