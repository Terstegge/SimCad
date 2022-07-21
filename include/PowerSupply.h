///////////////////////////////////////////////
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
///////////////////////////////////////////////
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
    PowerSupply(Pin & out, Pin & gnd) : _out(out), _gnd(gnd), _voltage(0) {
    }

    void setVoltage(double v) {
        _voltage = v;
    }

    void switchOn(bool startCThread = true) {
        // We have to disable short circuit exceptions during
        // startup, because there might be transient short
        // circuits during this phase.
        Net::_enable_sc_exceptions = false;
        _gnd = 0.0;
        _out = _voltage;
        Net::_enable_sc_exceptions = true;
        // Start the thread for capacity charge calculations
        if (startCThread) C::start();
    }

    void switchOff(bool stopCThread = true) {
        // Stop the thread for capacity charge calculations
        if (stopCThread) C::stop();
        // Disconnect the power
        NetSet nset;
        _out.setDrvNC(&nset);
        _gnd.setDrvNC(&nset);
    }

private:
    Pin &   _out;
    Pin &   _gnd;
    double  _voltage;
};

#endif // _INCLUDE_POWERSUPPLY_H_
