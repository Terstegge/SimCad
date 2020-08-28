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
// The struct 'State' represents the electrical
// state of a Pin or Net.
//
#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_

// Predefined States
struct State;
extern State LOW;
extern State HIGH;

class Pin;

#include <cmath>    // fabs()
#include <limits>   // infinity
#include <iostream>

#define SUPPLY_VOLTAGE  5.0
#define EPSILON         1e-4
#define INF             std::numeric_limits<float>::infinity()


class State {
public:
    // Default State constructor, creating
    // a NC State (Not Connected).
    State() { setNC(); }

    // Constructor to create a (strong) voltage source
    State(float u) : _isVS(true), _U(u), _R(0.0), _I(0.0) { }

    // Type conversion for booleans
    State(bool b) {
        setVS(b ? SUPPLY_VOLTAGE : 0.0, 0.0);
    }
    inline operator bool () const {
        return isNC() ? true : _U > (SUPPLY_VOLTAGE/2);
    }

    // Methods to set a voltage/current source or NC
    void setVS(float u, float r) { _U = u; _R = r; _isVS = true;  }
    void setCS(float i, float r) { _I = i; _R = r; _isVS = false; }
    void setR (float r)          { _R = r; }
    void setNC()   { _U = 0.0; _R = INF; _I = 0.0, _isVS = true;  }

    // Various getters
    inline bool  isVS() const { return _isVS; }
    inline float getU() const { return _isVS ? _U : _R * _I; }
    inline float getR() const { return _R; }
    inline float getG() const { return 1.0 / _R; }
    inline float getI() const {
        // NAN killer
        if (_isVS && _U==0.0) return 0.0;
        return _isVS ? _U / _R : _I;
    }

    // Methods to check NC and Strong states
    inline bool isStrong() const { return _R == 0.0; }
    inline bool isNC()     const { return _isVS ? _R == INF : _R == INF && _I == 0.0; }
    inline bool isHIGH()   const { return isStrong() && _U == SUPPLY_VOLTAGE; }
    inline bool isLOW()    const { return isStrong() && _U == 0.0; }

    // Comparison operators
    bool operator == (const State & rhs) const;
    inline bool operator != (const State & rhs) const {
        return !(*this == rhs);
    }

    // Calculation operators for parallel and serial circuits
    State & operator |= (const State & rhs);
    State & operator /= (const State & rhs);
    State & operator += (const State & rhs);
    State & operator -= (const State & rhs);

    State operator - () {
        State s = *this;
        _U *= -1.0;
        _I *= -1.0;
        return s;
    }

    // Stream output operator
    friend std::ostream & operator << (std::ostream & os, const State & rhs);

protected:
    bool    _isVS;
    float   _U;
    float   _R;
    float   _I;
};

State operator | (const State & lhs, const State & rhs);
State operator / (const State & lhs, const State & rhs);
State operator + (const State & lhs, const State & rhs);
State operator - (const State & lhs, const State & rhs);

#endif // INCLUDE_STATE_H_
