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
#include "PowerSupply.h"

double PowerSupply::MAX_VOLTAGE = 0.0;
double PowerSupply::MIN_VOLTAGE = 0.0;


PowerSupply::PowerSupply(Pin & out, Pin & gnd) : _out(out), _gnd(gnd), _voltage(0) {
}

void PowerSupply::setVoltage(double v) {
    _voltage = v;
    if (v > MAX_VOLTAGE) MAX_VOLTAGE = v;
    if (v < MIN_VOLTAGE) MIN_VOLTAGE = v;
}

void PowerSupply::switchOn(bool startCThread) {
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

void PowerSupply::switchOff(bool stopCThread) {
    // Stop the thread for capacity charge calculations
    if (stopCThread) C::stop();
    // Disconnect the power
    NetSet nset;
    _out.setDrvNC(&nset);
    _gnd.setDrvNC(&nset);
}

