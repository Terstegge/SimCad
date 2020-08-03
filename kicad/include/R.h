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
            if (p[1] == LOW)  p[2].setDrvState(PD, nets );
            if (p[1] == HIGH) p[2].setDrvState(PU, nets );
        });
        p[2].attach([this](NetSet * nets) {
            if (p[2] == LOW)  p[1].setDrvState(PD, nets );
            if (p[2] == HIGH) p[1].setDrvState(PU, nets );
        });
    }
};

#endif // _R_H_
