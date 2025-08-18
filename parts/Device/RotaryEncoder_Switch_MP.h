/////////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
/////////////////////////////////////////////////
//
//
//
#ifndef _INCLUDE_ROTARYENCODER_SWITCH_MP_H_
#define _INCLUDE_ROTARYENCODER_SWITCH_MP_H_

#include "Bus.h"

class RotaryEncoder_Switch_MP : Named {
public:
    Pin A;
    Pin B;
    Pin C;
    Pin S1;
    Pin S2;
    Pin MP;

    RotaryEncoder_Switch_MP(const std::string & name) : Named(name),
        NAME(A), NAME(B), NAME(C), NAME(S1), NAME(S2), NAME(MP) {
    }

protected:

};
#endif // _INCLUDE_ROTARYENCODER_SWITCH_MP_H_
