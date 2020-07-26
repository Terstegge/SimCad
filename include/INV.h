#ifndef _INV_H_
#define _INV_H_

#include "Named.h"
#include "Bus.h"

#include <iostream>
using namespace std;

class INV : public Named {
public:
    Bus<4> p;
    Pin &    VCC;
    Pin &    GND;

    INV(const string & name="") : Named(name), NAME(p), GND(p[0]), VCC(p[3])
    {
        p[1].attach([this](NetSet * nets) {
            p[2].setDrvState( !(bool)p[1], nets );
        });
        p[2].setDrvState( !(bool)p[1], nullptr );
    }

};

#endif // _INV_H_
