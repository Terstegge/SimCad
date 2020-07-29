#ifndef _NAND_H_
#define _NAND_H_

#include "Bus.h"
#include "Named.h"

template<int N>
class NAND : public Named {
public:
    Bus<N+3> p;
    Pin &    VCC;
    Pin &    GND;

    NAND(const string & _name="") : Named(_name), NAME(p), GND(p[0]), VCC(p[N+2])
    {
        for(int i=1; i <= N; ++i) {
            p[i].attach( [this](NetSet * nets) {
                p[N+1].setDrvState( this->calculate(p), nets );
            } );
        }
        p[N+1] = calculate(p);
    }

    bool calculate(Bus<N+3> & p)
    {
        bool res = true;
        for(int i=1; i <= N; ++i) {
            res &= (bool)p[i];
            if (!res) break;
        }
        return !res;
    }

#if 0
    friend ostream & operator << (ostream & os, const NAND & rhs)
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

#endif // _NAND_H_
