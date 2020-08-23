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

#include "Part.h"
#include "Pin.h"
#include "Narray.h"

#include <iostream>
using namespace std;

class VSOURCE : public Part {
public:
    Narray<Pin, 3> p;
    float         _U; // Voltage
    bool          _on = false;

    VSOURCE(const std::string & name, float u)
    : Part(name), NAME(p), _U(u)
    {
        // Set the part pointers
        p[1].setPartPtr(this);
        p[2].setPartPtr(this);
        // Attach handler for negative pin
        p[1].attach([this](NetSet & nets) {
            cout << p[1] << " " << p[2] << endl;
            if (!_on) return;
            // Let the positive pin follow the negative pin with
            // the correct voltage difference (_U)
            p[2].setDrvState( State(p[1].getInpState()._U + _U, 0.0), nets );
        });
    }

    void on() {
        _on = true;
        p[2] = State(p[1].getInpState()._U + _U, 0.0);
    }
};

#endif /* INCLUDE_VSOURCE_H_ */
