/////////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
/////////////////////////////////////////////////
//
// Low level implementation of a generic gate
// with N inputs (p[1]...p[n]):
//
// p[0]       is the power input GND
// p[1]..p[N] are the input Pins
// p[N+1]     is the output Pin  OUT
// p[N+2]     is the power input VCC
//
#ifndef _INCLUDE_GATE_H_
#define _INCLUDE_GATE_H_

#include "Pin.h"
#include "Narray.h"
#include <iostream>
#include <string>

template<int N>
class Gate : public Named {
public:
    Narray<Pin, N+3> p;
    Pin &    VCC;
    Pin &    GND;
    Pin &    OUT;
    bool     on;    // true if power is switched on

    Gate(const std::string & name)
    : Named(name), NAME(p), VCC(p[N+2]), GND(p[0]), OUT(p[N+1]), on(false)
    {
        // Attach power signals
        VCC.attach( [this](NetSet * nset) {
            on  = VCC.isVCC() && GND.isGND();
            if (on) {
                calculate(nset);
            } else {
                setOUTnc(nset);
            }
        });
        GND.attach( [this](NetSet * nset) {
            on  = VCC.isVCC() && GND.isGND();
            if (on) {
                calculate(nset);
            } else {
                setOUTnc(nset);
            }
        });
        // Attach input signal handlers
        for(int i=1; i <= N; ++i) {
            p[i].attach( [this](NetSet * nset) {
                if (on) {
                    calculate(nset);
                } else {
                    setOUTnc(nset);
                }
            });
        }
    }

    virtual ~Gate() {
    }

    // The method to calculate the result of a specific gate.
    // Has to be provided by the concrete gate classes.
    virtual void calculate(NetSet * nset) = 0;

    // Utility method to set the digital OUT Pin
    void setOUTbool(bool b, NetSet *nset) {
        if (b) {
            if (!OUT.isDrvVS(VCC.U())) {
                OUT.setDrvVS(VCC.U(), nset);
                if (OUT.getNet()->hasLoad()) {
                    VCC._Rdrv = OUT.getNet()->Rload();
                    VCC._Idrv = [&] (double U) -> double {
                        return OUT.getNet()->Isum(U);
                    };
                    GND._Rdrv = INF;
                    GND._Idrv = nullptr;
                    nset->insert(VCC._netPtr);
                    nset->insert(GND._netPtr);
                }
            }
        } else {
            if (!OUT.isDrvVS(GND.U())) {
                OUT.setDrvVS(GND.U(), nset);
                if (OUT.getNet()->hasLoad()) {
                    VCC._Rdrv = INF;
                    VCC._Idrv = nullptr;
                    GND._Rdrv = OUT.getNet()->Rload();
                    GND._Idrv = [&] (double U) -> double {
                        return OUT.getNet()->Isum(U);
                    };
                    nset->insert(VCC._netPtr);
                    nset->insert(GND._netPtr);
                }
            }
        }
    }

    void setOUTnc(NetSet *nset) {
        if (!OUT.isDrvNC()) {
            OUT.setDrvNC(nset);
            if (OUT.getNet()->hasLoad()) {
                VCC.setDrvNC(nset);
                GND.setDrvNC(nset);
            }
        }
    }

    friend std::ostream & operator << (std::ostream & os, const Gate<N> & rhs) {
        os << "Gate " << rhs.getName() << std::endl;
        for(int i=1; i <= N; ++i) {
            os << "Input  "   << rhs.p[i].getName();
            os << " reading " << rhs.p[i].getInpState();
            os << std::endl;
        }
        os << "Output "   << rhs.OUT.getName();
        //        os << " driving " << drive << rhs.OUT;
        os << std::endl;
        return os;
    }
};

#endif // _INCLUDE_GATE_H_
