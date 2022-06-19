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
#include "Pin.h"
#include "Config.h"
#include "SimCadException.h"
#include <iostream>

bool Pin::_show_drive_state = false;

Pin::Pin(const std::string & name) : Named(name), _Udrv(0.0)
{
    // Create a new Net and insert this Pin into it
    _netPtr = new Net(name);
    _netPtr->_pins.push_back(this);
    _Rdrv = INF;
}

void Pin::connect_to(Pin & p) {
    _netPtr->merge_net(_netPtr, p._netPtr);
}

void Pin::setDrvVS(double u, NetSet * nset) {
    _Udrv = u;
    _Rdrv = 0;
    _Idrv = nullptr;
    // Update the Net either within a already running
    // update (nset != nullptr) or triggering a new update.
    if (nset) {
        nset->insert(_netPtr);
    } else {
        _netPtr->update();
    }
}

void Pin::setDrvBool(bool b, NetSet * nset) {
    setDrvVS(b ? SUPPLY_VOLTAGE : 0.0, nset);
}

void Pin::setDrvNC(NetSet * nset) {
    _Rdrv = INF;
    _Idrv = nullptr;
    // Update the Net either within a already running
    // update (nset != nullptr) or triggering a new update.
    if (nset) {
        nset->insert(_netPtr);
    } else {
        _netPtr->update();
    }
}

void Pin::attach(UFUNC u) {
    if (_update) {
        throw updateInUseException(this);
    }
    _update = u;
}

double Pin::I() const {
    if (isDrvNC()) return 0.0;
    return isDrvVS() ? -_netPtr->Isum(U(), this) : _Idrv(U());
}

std::ostream& operator <<(std::ostream &os, const Pin &p) {
    os << p.getName() << ": [";
    if (Pin::_show_drive_state) {
        // Show the driving values of this Pin
        os << "Drive ";
        if (p.isDrvNC()) {
            os << "NC]";
        } else if (p.isDrvVS()) {
            os << p._Udrv << "V Source]";
        } else {
            os << p._Rdrv << "Ω";
            if (p._Idrv) {
                os << ", " << p._Idrv(p.U()) << "A";
            }
            os << "]";
        }
    } else {
        // Standard output of a Pin, showing the Net values
        if (p.isNC()) {
            os << "NC]";
        } else if (p.isVS()) {
            os << p.U() << " V Source, ";
            os << p.getNet()->Rw(&p) << " Ω, ";
            os << p.I() << " A]";
        } else {
            os << p.U() << " V, ";
            os << p.R() << " Ω, ";
            os << p.I() << " A]";
        }
    }
    // Reset manipulator. It only has effect
    // on the next output operation!
    Pin::_show_drive_state = false;
    return os;
}

