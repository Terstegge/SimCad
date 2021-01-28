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
// A generic voltage source for simulation.
// p[1] is the negative pin.
// p[2] is the positive pin,
//
#ifndef _INCLUDE_VSOURCE_H_
#define _INCLUDE_VSOURCE_H_

#include "TwoPole.h"

class VSOURCE : public TwoPole {
public:
    VSOURCE(const std::string & name, float u) : TwoPole(name), _U(u) {
        setG( INF );
    }

    void p1_callback() override {
        p[2].Ud += _U;
    }
    void p2_callback() override {
        p[1].Ud -= _U;
    }

private:
    float _U;
};

#endif // _INCLUDE_VSOURCE_H_
