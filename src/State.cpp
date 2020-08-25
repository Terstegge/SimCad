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

// Strong LOW State
State LOW  (0.0, INF);
// Strong HIGH State
State HIGH (5.0, INF);

// Output operator
std::ostream & operator << (std::ostream & os, const State & s)  {
    if (s.isNC()) {
        os << "NC";
    } else if (s == HIGH) {
        os << "H";
    } else if (s == LOW) {
        os << "L";
    } else {
        os << "[";
        os << s._U << " V, ";
        os << 1.0 / s._G;
        os << " Ω]";
    }
    return os;
}
