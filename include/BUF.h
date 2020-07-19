#ifndef _BUFFER_G_H_
#define _BUFFER_G_H_

#include "Named.h"
#include "Bus.h"

#include <iostream>
using namespace std;

class BUF : public Named {
public:
    Bus<5> p;

    BUF(const string & name="") : Named(name), NAME(p)
    {
        p[1].attach([this](NetSet * nets) {
            p[2].setDrvState( (bool)p[1], nets );
        });
        p[2].setDrvState( (bool)p[1], nullptr );
    }

};

#endif // _BUFFER_G_H_
