///////////////////////////////////////////////
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//  A simulation package for digital circuits
//  (c) 2020  A. Terstegge
///////////////////////////////////////////////
//
// Low-level implementation of a Si diode
// (forward voltage 0.7V at 10mA)
//
#ifndef _INCLUDE_1N4148_H_
#define _INCLUDE_1N4148_H_

#include "DIODE.h"

class _1N4148 : public DIODE {
public:
    _1N4148(const string & name="") : DIODE(name, 0.7) { }
};

#endif // _INCLUDE_1N4148_H_
