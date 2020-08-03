#ifndef _1N4148_H_
#define _1N4148_H_

#include "Pin.h"
#include "Narray.h"
#include "Named.h"

class _1N4148 : public Named {

public:
    Narray<Pin, 3> p;

    Pin & K, & A;

    _1N4148(const string & name="") :
        Named(name), NAME(p), K(p[1]), A(p[2])
    {
        K.attach([this](NetSet * nets){this->update(nets);} );
        update(nullptr);
    }

    void update(NetSet * nets) {
        if ((State)K == LOW) {
            A.setDrvState(LOW, nets );
        } else {
            A.setDrvState(NC, nets);
        }
    }

};

#endif // _1N4148_H_
