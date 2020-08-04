/*
 * This file is part of the DigiSim Software -
 * a simulation package for digital circuits.
 *
 * (c) 2020 A. Terstegge
 *
 * The enum 'State' reflects the driving (output)
 * state of a single pin:
 * LOW:   The pin is tied to GND -> logic LOW
 * HIGH:  The pin is tied to VCC -> logic HIGH
 * PD:    The pin is Pulled Down by a resistor
 * PU:    The pin is Pulled Up by a resistor
 * NC:    The pin is not connected -> high Z state
 *
 */

#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
using namespace std;

// The State enum. We do not use C++11 enums classes,
// because we need easy conversion to integers in
// various places. The integer values are chooses so
// that the LSB will reflect the input interpretation
// of every State (NC will be seen as logic '1').
enum State { LOW=0, HIGH=1, PD=2, PU=3, NC=5 };

// Method to check if the State is LOW or HIGH
// (strong).
bool isStrong(State s);

// Convert a State to a boolean. This is
// needed when a State is used as an input.
// NC Pins (not connected) are treated as
// HIGH (true), which is the normal behavior
// of TTL chips.
bool toBool(State s);

// Convert a boolean to a State. This is
// needed when State has to be set in an
// output Pin. Only LOW and HIGH are
// possible result values;
State toState(bool s);

// Output operator with verbose output
ostream & operator << (ostream & os, const State s);

// Output operator with short (one character) output
ostream & operator <<= (ostream & os, const State s);

#endif // _STATE_H_
