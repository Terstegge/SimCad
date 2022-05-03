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
#include "Pin.h"
#include "Config.h"
#include <iostream>

bool Pin::_show_drive_state = false;

Pin::Pin(const std::string & name) : Named(name),
    _Uvs(0.0), _isVS(false)
{
	// Create a new Net and insert this Pin into it
    _netPtr = new Net(name);
    _netPtr->_pins.push_back(this);
}

void Pin::connect_to(Pin & p) {
    _netPtr->merge_net(_netPtr, p._netPtr);
}

void Pin::setIDrv(IFUNC f, NetSet * nset) {
    // Set the driving function
    _Idrv = f;
    // Update the Net either within a already running update
    // (nset != nullptr) or triggering a new update.
    if (nset) {
        nset->insert(_netPtr);
    } else {
        _netPtr->update();
    }
}

void Pin::setDrvVS(double u, NetSet * nset) {
    _isVS = true;
    _Uvs  = u;
    setIDrv(nullptr, nset);
}

void Pin::setDrvBool(bool b, NetSet * nset) {
    setDrvVS(b ? SUPPLY_VOLTAGE : 0.0, nset);
}

void Pin::setDrvNC(NetSet * nset) {
    _isVS = false;
    setIDrv(nullptr, nset);
}

double Pin::U() const {
    return _netPtr->U;
}

double Pin::R() const {
    return isDrvVS() ? _netPtr->R() : _netPtr->Rd();
}

double Pin::I() const {
    if (isDrvNC()) return 0.0;
    return isDrvVS() ? -_netPtr->Isum(U()) : _Idrv(U());
}

std::ostream& operator <<(std::ostream &os, const Pin &p) {
    os << p.getName() << ": [";
    if (!Pin::_show_drive_state) {
        // Standard output of a Pin, showing the Net values
        if (p.isNC()) {
            os << "NC]";
        } else {
            os << p.U() << " V, ";
            os << p.R() << " Ohm, ";
            os << p.I() << " A]";
        }
    } else {
        // Show the driving values of this Pin
        if (p.isDrvNC()) {
            os << "NC]";
        } else if (p.isDrvVS()) {
            os << p._Uvs << " V Source]";
        } else {
            if (p._Idrv) {
                double dU = 0.2;
                double U  = p.getNet()->zero(p._Idrv);
                double R  = dU / (p._Idrv(U + dU/2.0) - p._Idrv(U - dU/2.0));
                os << U << " V, ";
                os << R << " Ohm";
            } else {
                os << "no drive]";
            }
        }
    }
    // Reset manipulator. It only has effect
    // on the next output operation!
    Pin::_show_drive_state = false;
    return os;
}

