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
#ifndef INCLUDE_ISOURCE_H_
#define INCLUDE_ISOURCE_H_

#include "TwoPole.h"

class ISOURCE : public TwoPole {
public:
    float _I;

    ISOURCE(const std::string & name, float i) : TwoPole(name) {
        _I = i;
        _U = INF;   // Make sure _U == 0.0 is reported locally the first time!
    }

    bool calculate() override {
        State p1s = p[1].getInpState();
        State p2s = p[2].getInpState();
        // Check if both Pins are connected
        if (p1s.isNC() || p2s.isNC()) {
            return false;
        }

        float old_U = _U;
        _U = p2s._U - p1s._U;
        float R = 1.0/p1s._G + 1.0/p2s._G;
        _U -= _I * R;
        _R  = 0;
        return _U != old_U;
    }
};

#endif /* INCLUDE_VSOURCE_H_ */
