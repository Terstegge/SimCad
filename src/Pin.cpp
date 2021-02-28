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
bool Pin::_show_drive_state = false;

Pin::Pin(const std::string & name) : Named(name),
     Ud(_Ud),  Gd(_Gd),  Id(_Id),
    _Ud(0.0), _Gd(0.0), _Id(0.0),
    _netPtr (Net::create_net(name))
{
    _netPtr->_pins.push_back(this);
}

void Pin::connect_to(Pin & p) {
    _netPtr->merge_net(_netPtr, p._netPtr);
}

void Pin::setDrvState(double u, double g, double i, ElementSet *nets) {
    if (_Ud != u || _Gd != g || _Id != i) {
        _Ud = u;
        _Gd = g;
        _Id = i;
        if (nets) {
            nets->insert(_netPtr);
        } else {
            _netPtr->update();
        }
    }
}


std::ostream& operator <<(std::ostream &os, const Pin &p) {
    os << p.getName() << ": [";
    if (Pin::_show_drive_state) {
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
            os << p._netPtr->U        << " V, ";
            os << 1.0 / p._netPtr->Gi << " Ω, ";
            os << p.I()               << " A]";
        }
    }
    // Reset manipulator. It only has effect
    // on the next output operation!
    Pin::_show_drive_state = false;
    return os;
}

