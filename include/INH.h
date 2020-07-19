#ifndef _INH_H_
#define _INH_H_

#include "Bus.h"
#include "Named.h"

template<int N>
class INH : public Named {
public:
    Bus<N+4> p;

    INH(const string & name="") : Named(name), NAME(p)
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
        bool res = true;
        for(int i=1; i < N; ++i) {
            res &= (bool)p[i];
            if (!res) break;
        }
        res &= !(bool)p[N];
        return res;
    }

#if 0
    friend ostream & operator << (ostream & os, const INH & rhs)
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

#endif // _INH_H_
