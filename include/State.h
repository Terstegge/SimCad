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
// The enum 'State' reflects the driving (output)
// state of a Pin or the resulting input state
// of a Pin or Net. We do not use C++11 enums classes,
// because we need easy conversion to integers in
// various places. The integer values are chooses so
// that the LSB will reflect the input interpretation
// of every State (NC will be seen as logic '1'):
//
// LOW  (0):  The Pin is tied to GND -> logic LOW
// HIGH (1):  The Pin is tied to VCC -> logic HIGH
// PD:  (2):  The Pin is Pulled Down by a resistor
// PU:  (3):  The Pin is Pulled Up by a resistor
// NC:  (5):  The Pin is not connected -> high Z state
//
//   +------------- NC if set
//   |    +-------- weak if set (PD/PU)
//   |    |    +--- overall state (LOW/HIGH) and input value
//   |    |    |
// Bit2 Bit1 Bit0
//
#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
using std::ostream;

enum State { LOW=0, HIGH=1, PD=2, PU=3, NC=5 };

// Method to check if the State is LOW or HIGH (strong).
bool isStrong(State s);

// Method to check if the State is PD or PU (weak).
bool isWeak(State s);

// Method to convert a State into a strong one
State toStrong(State s);

// Method to convert a State into a weak one
State toWeak(State s);

// Convert a State to a boolean. This is
// needed when a State is used as an input.
// NC Pins (not connected) are treated as
// HIGH (true), which is the normal behavior
// of TTL chips.
bool toBool(State s);

// Convert a boolean to a State. This is
// needed when State has to be set in an
// output Pin. Only LOW and HIGH are
// possible result values.
State toState(bool s);

// Output operator
ostream & operator << (ostream & os, const State & s);

#endif // _STATE_H_
