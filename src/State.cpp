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
#include "ShortCircuitEx.h"

// Strong LOW State
State LOW  (0.0f);
// Strong HIGH State
State HIGH (5.0f);

bool State::operator == (const State & rhs) const {
    if (isNC() && rhs.isNC()) {
        return true;
    } else if ((_U == rhs._U) &&
               (_R == rhs._R) &&
               (_I == rhs._I))
    {
        return true;
    } else {
        return (fabs(_U - rhs._U) < EPSILON) &&
               (fabs(_R - rhs._R) < EPSILON) &&
               (fabs(_I - rhs._I) < EPSILON);
    }
}


State & State::operator |= (const State & rhs) {
    if (rhs.isNC()) return *this;
    if (isStrong() && !rhs.isStrong()) return *this;
    if (isNC()) {
        (*this) = rhs;
        return *this;
    }
    if (!isStrong() && rhs.isStrong()) {
        (*this) = rhs;
        return *this;
    }
    if (isStrong() && rhs.isStrong() && (_U != rhs._U)) {
        throw short_circuit_exception(*this, rhs);
    }
    // Calculate result
    _I = getI() + rhs.getI();
    _R = 1.0 / (getG() + rhs.getG());
    _U = _R * _I;
    return *this;
}


// Substract rhs from this
State & State::operator /= (const State & rhs) {
    if (rhs.isNC()) return *this;
    if (isStrong() && !rhs.isStrong()) return *this;
    if (isNC()) {
        (*this) = rhs;
        return *this;
    }
    if (!isStrong() && rhs.isStrong()) {
        (*this) = rhs;
        return *this;
    }
    if (isStrong() && rhs.isStrong() && (_U != rhs._U)) {
        throw short_circuit_exception(*this, rhs);
    }
//    if (*this == rhs) {
//        setNC();
//        return *this;
//    }

//    if (isNC()     || rhs.isNC() ||
//        isStrong() || rhs.isStrong()) {
//        return *this;
//    }
    _I = getI() - rhs.getI();
    _R = 1.0 / (getG() - rhs.getG());
    _U = _R * _I;
    return *this;
}


State & State::operator += (const State & rhs) {
    if (!isNC() && !rhs.isNC()) {
        _U += rhs.getU();
        _R += rhs.getR();
        _I += rhs.getI();
    } else {
        setNC();
    }
    return *this;
}

State & State::operator -= (const State & rhs) {
    if (*this == rhs) {
        setNC();
        return *this;
    }
    if (!isNC() && !rhs.isNC()) {
        _U -= rhs.getU();
        _R -= rhs.getR();
        _I -= rhs.getI();
    } else {
        setNC();
    }
    return *this;
}

// Output operator
std::ostream & operator << (std::ostream & os, const State & rhs)  {
    if (rhs.isNC()) {
        os << "NC";
    } else {
        os << "[";
        /*if (rhs._isVS)*/  os << rhs._U << " V, ";
        /*else          */  os << rhs._I << " A, ";
        os << rhs._R << " Ω]";
    }
    return os;
}

State operator | (const State & lhs, const State & rhs) {
    State  s {lhs};
    return s |= rhs;
}

State operator / (const State & lhs, const State & rhs) {
    State  s {lhs};
    return s /= rhs;
}

State operator + (const State & lhs, const State & rhs) {
    State  s {lhs};
    return s += rhs;
}

State operator - (const State & lhs, const State & rhs) {
    State  s {lhs};
    return s -= rhs;
}
