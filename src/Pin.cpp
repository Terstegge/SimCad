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
bool Pin::_drv = false;

Pin::Pin(const std::string & name) : Named(name),
    Ud(0.0), Gd(0.0), Id(0.0),
    _netPtr (nullptr),
    _partPtr(nullptr) {
}

void Pin::connect_to(Pin & p) {
    NetPtr net;
    if (this->_netPtr && p._netPtr) {
        if (this->_netPtr == p._netPtr) return;
        // Merge two NETs
        NetPtr net    = this->_netPtr;
        NetPtr remote = p._netPtr;
        // Insert remote Pins to local NET
        net->_pins.insert( net->_pins.end(),
                           remote->_pins.begin(),
                           remote->_pins.end());
        // Set Net pointer to local Net
        for (Pin * p : remote->_pins) {
            p->_netPtr = net;
        }
    } else if (this->_netPtr) {
        net = this->_netPtr;
        net->_pins.push_back(&p);
        p._netPtr = net;
    } else if (p._netPtr) {
        net = p._netPtr;
        net->_pins.push_back(this);
        _netPtr = net;
    } else {
        net = Net::create_net(_name);
        net->_pins.push_back(this);
        net->_pins.push_back(&p);
        _netPtr   = net;
        p._netPtr = net;
    }
    net->update();
}

void Pin::setDrvState(float u, float g, float i, NetSet *nets) {
    if (Ud != u || Gd != g || Id != i) {
        Ud = u;
        Gd = g;
        Id = i;
        if (_netPtr) {
            if (nets) {
                nets->insert(_netPtr);
            } else {
                _netPtr->update();
            }
        }
    }
}


std::ostream& operator <<(std::ostream &os, const Pin &p) {
    os << p.getName() << ": [";
    if (Pin::_drv) {
        if (p.isDrvNC()) {
            os << "NC]";
        } else {
            os << p.Ud       << " V, ";
            os << 1.0 / p.Gd << " Ω, ";
            os << p.Id       << " A]";
        }
    } else {
        if (p.isNC()) {
            os << "NC]";
        } else {
            os << p.U()        << " V, ";
            os << 1.0 / p.Gi() << " Ω, ";
            os << p.I()        << " A]";
        }
    }
    // Reset manipulator. It only has effect
    // on the next output operation!
    Pin::_drv = false;
    return os;
}

