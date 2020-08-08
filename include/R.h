#ifndef _R_H_
#define _R_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class R : public Named {

public:
    Narray<Pin, 3> p;

    R(const string & name) : Named(name), NAME(p)
    {
        p[1].attach([this](NetSet * nets) {
            p[2].setDrvState( toWeak((State)p[1]), nets );
        });
        p[2].attach([this](NetSet * nets) {
            p[1].setDrvState( toWeak((State)p[2]), nets );
        });
    }

};

#endif // _R_H_
