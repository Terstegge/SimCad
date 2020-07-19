#ifndef _INV_H_
#define _INV_H_

#include "Named.h"
#include "Bus.h"

#include <iostream>
using namespace std;

class INV : public Named {
public:
    Bus<5> p;

    INV(const string & name="") : Named(name), NAME(p)
    {
        p[1].attach([this](NetSet * nets) {
            p[2].setDrvState( !(bool)p[1], nets );
        });
        p[2].setDrvState( !(bool)p[1], nullptr );
    }

};

#endif // _INV_H_
