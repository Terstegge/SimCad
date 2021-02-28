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
// with N inputs (p[1]...p[n]):
//
// p[0]       is the power input GND
// p[1]..p[N] are the input Pins
// p[N+1]     is the output Pin  OUT
// p[N+2]     is the power input VCC
//
#ifndef INCLUDE_GATE_H_
#define INCLUDE_GATE_H_

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
        // Set the part pointers
//        for (Pin & pin : p) {
//            pin.setPartPtr(this);
//        }
        // Attach power signals
        VCC.attach( [this](ElementSet * esp) {
            on  = VCC.isVCC() && GND.isGND();
            if (on) {
                calculate(esp);
            } else {
                OUT.setDrvNC(esp);
            }
        });
        GND.attach( [this](ElementSet * esp) {
            on  = VCC.isVCC() && GND.isGND();
            if (on) {
                calculate(esp);
            } else {
                OUT.setDrvNC(esp);
            }
        });
        // Attach input signal handlers
        for(int i=1; i <= N; ++i) {
            p[i].attach( [this](ElementSet * esp) {
                if (on) {
                    calculate(esp);
                } else {
                    OUT.setDrvNC(esp);
                }
            });
        }
    }

    virtual ~Gate() {
    }

    // The method to calculate the result of a specific gate.
    // Has to be provided by the concrete gate classes.
    virtual void calculate(ElementSet * esp) = 0;

    friend std::ostream & operator << (std::ostream & os, const Gate<N> & rhs) {
        os << "Gate " << rhs.getName() << std::endl;
        for(int i=1; i <= N; ++i) {
            os << "Input  "   << rhs.p[i].getName();
            os << " reading " << rhs.p[i].getInpState();
            os << std::endl;
        }
        os << "Output "   << rhs.OUT.getName();
        os << " driving " << drive << rhs.OUT;
        os << std::endl;
        return os;
    }
};

#endif // INCLUDE_GATE_H_
