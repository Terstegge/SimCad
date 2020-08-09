///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  A simulation package for digital circuits
//
//  (c) 2020  A. Terstegge
//
///////////////////////////////////////////////
//
// Low level implementation of a generic gate
// with N inputs (p[1]...p[n]).
// p[0]   is the power input GND
// p[N+2] is the power input VCC
// p[N+1] is the output Pin  OUT
//
#ifndef _GATE_H_
#define _GATE_H_

#include "Narray.h"
#include "Named.h"

template<int N>
class GATE : public Named {
public:
    Narray<Pin, N+3> p;
    Pin &    VCC;
    Pin &    GND;
    Pin &    OUT;
    bool     on;    // true if power is applied

    GATE(const string & name)
     : Named(name), NAME(p),
       VCC(p[N+2]), GND(p[0]), OUT(p[N+1]), on(false)
    {
        // Attach power signals
        VCC.attach( [this](NetSet * nets) {
            on = (VCC == HIGH) && (GND == LOW);
            OUT.setDrvState( on ? this->calculate() : NC, nets);
        });
        GND.attach( [this](NetSet * nets) {
            on = (VCC == HIGH) && (GND == LOW);
            OUT.setDrvState( on ? this->calculate() : NC, nets);
        });
        // Attach input signals
        for(int i=1; i <= N; ++i) {
            p[i].attach( [this](NetSet * nets) {
                OUT.setDrvState( on ? this->calculate() : NC, nets );
            });
        }
    }

    virtual ~GATE() { }

    virtual State calculate() = 0;

    friend ostream & operator << (ostream & os, const GATE<N> & rhs)
    {
        os << rhs.getName() << ": (";
        for(int i=1; i <= N; ++i) {
            os << rhs.p[i].getInpState();
            os << " ";
        }
        os << "-> ";
        os <<= rhs.p[N+1].getDrvState();
        os << ")";
        return os;
    }

};

#endif // _GATE_H_
