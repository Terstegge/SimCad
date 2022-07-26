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
// Base class for various power supplies
//
#ifndef _INCLUDE_POWERSUPPLY_H_
#define _INCLUDE_POWERSUPPLY_H_

#include "Net.h"
#include "Pin.h"
#include "C.h"

class PowerSupply {
public:
    PowerSupply(Pin & out, Pin & gnd);

    void setVoltage(double v);
    void switchOn(bool startCThread = true);
    void switchOff(bool stopCThread = true);

    static double MAX_VOLTAGE;
    static double MIN_VOLTAGE;

private:
    Pin &   _out;
    Pin &   _gnd;
    double  _voltage;
};

#endif // _INCLUDE_POWERSUPPLY_H_
