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
#ifndef INCLUDE_VSOURCE_H_
#define INCLUDE_VSOURCE_H_

#include "TwoPole.h"

class VSOURCE : public TwoPole {
public:

    VSOURCE(const std::string & name, float u) : TwoPole(name) {
        // Ideal voltage source with Ri=0
        _R = 0.0;
        _U = u;
    }

    bool calculate() override {
        // The values are already set in the constructor,
        // and will not change. So we have nothing to do here...
        return false;
    }
};

#endif /* INCLUDE_VSOURCE_H_ */
