#ifndef _OR_H_
#define _OR_H_

#include "Bus.h"
#include "Named.h"

template<int N>
class OR : public Named {
public:
    Bus<N+4> p;

    OR(const string & name="") : Named(name), NAME(p)
    {
        for(int i=1; i <= N; ++i) {
            p[i].attach( [this](NetSet * nets) {
                p[N+1].setDrvState( this->calculate(p), nets );
            } );
        }
        p[N+1] = calculate(p);
    }

    bool calculate(Bus<N+4> & p)
    {
        bool res = false;
        for(int i=1; i <= N; ++i) {
            res |= (bool)p[i];
            if (res) break;
        }
        return res;
    }

#if 0
    friend ostream & operator << (ostream & os, const OR & rhs)
    {
        os << rhs.getName() << ": (";
        for (const Pin & p : rhs.in) {
            os << p.getInpState() << " ";
        }
        os << "-> " << (State)rhs.out << ")";
        return os;
    }
#endif

};

#endif // _OR_H_

