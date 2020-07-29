#ifndef _BUFFER_G_H_
#define _BUFFER_G_H_

#include "Named.h"
#include "Bus.h"

#include <iostream>
using namespace std;

class BUF : public Named {
public:
    Bus<4> p;
    Pin &    VCC;
    Pin &    GND;

    BUF(const string & _name="") : Named(_name), NAME(p), GND(p[0]), VCC(p[3])
    {
        p[1].attach([this](NetSet * nets) {
            p[2].setDrvState( (bool)p[1], nets );
        });
        p[2].setDrvState( (bool)p[1], nullptr );
    }

};

#endif // _BUFFER_G_H_
