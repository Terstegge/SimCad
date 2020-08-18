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
#include "State.h"

State LOW  (false, 0.0, 0.0);
State HIGH (false, 5.0, 0.0);
//State PD   (false, 0.0, 470.0);
//State PU   (false, 5.0, 470.0);
State NC   (true,  0.0, 0.0);


#if 0
bool isStrong(State s) {
    // Mask away the LSB bit (LOW/HIGH) 
    // The remainder has to be 0:
    // --> weak bit not set
    // --> NC bit not set
    return !(s & 0x06);
}

bool isWeak(State s) {
    // Mask away the LSB bit (LOW/HIGH) and
    // the NC-bit. The result has to be != 0:
    // --> weak bit set
    return (s & 0x2);
}

State toStrong(State s) {
    // Mask away the weak bit
    // --> state will be strong or NC
    return State(s & 0x5);
}

State toWeak(State s) {
    // Add weak bit if not NC
    return State(s != NC ? s | 0x2 : NC);
}

// Mask away the weak bit and the NC bit.
// The remainder is the resulting boolean
// value (NC is interpreted as HIGH).
bool toBool(State s) {
    return s & 0x01;
}

State toState(bool s) {
    return s ? HIGH : LOW;
}

#endif

// Output operator
ostream & operator << (ostream & os, const State & s)  {
#if 0
    os << "[";
    if (s.getNC()) os << "NC";
    else {
      os << s.getU() << " ";
      os << s.getR();
    }
    os << "]";
#endif
    if (s.getNC()) {
        os << "x";
    }
    else if (s.isStrong()) {
        if (s._U == 5.0) {
            os << "H";
        } else
        if (s._U == 0.0) {
            os << "L";
        } else
            os << "M";
    }
    else {
        os << "[";
        os << s.getU() << " ";
        os << s.getR();
        os << "]";
    }
    return os;
}
