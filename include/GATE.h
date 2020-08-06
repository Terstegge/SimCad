#ifndef _GATE_H_
#define _GATE_H_

#include "Bus.h"
#include "Named.h"

template<int N>
class GATE : public Named {
public:
    Bus<N+3> p;
    Pin &    VCC;
    Pin &    GND;
    Pin &    OUT;
    bool     on;

    GATE(const string & _name)
     : Named(_name), NAME(p), VCC(p[N+2]), GND(p[0]), OUT(p[N+1]), on(false)
    {
        // Attach power signals
        VCC.attach( [this](NetSet * nets) {
            on = (VCC == HIGH) && (GND == LOW);
            if (on) {
                OUT.setDrvState( on ? this->calculate() : NC, nets);
            }
        });
        GND.attach( [this](NetSet * nets) {
            on = (VCC == HIGH) && (GND == LOW);
            if (on) {
                OUT.setDrvState( on ? this->calculate() : NC, nets);
            }
        });
        // Attach input signals
        for(int i=1; i <= N; ++i) {
            p[i].attach( [this](NetSet * nets) {
                if (on) {
                    OUT.setDrvState( this->calculate(), nets );
                }
            });
        }
    }

    virtual State calculate() = 0;

    friend ostream & operator << (ostream & os, const GATE<N> & rhs)
    {
        os << rhs.getName() << ": (";
        for(int i=1; i <= N; ++i) {
            os <<= rhs.p[i].getInpState();
            os << " ";
        }
        os << "-> ";
        os <<= rhs.p[N+1].getDrvState();
        os << ")";
        return os;
    }

};

#endif // _GATE_H_
