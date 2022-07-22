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
#ifndef _PARTS_CONNECTOR_USB_B_H_
#define _PARTS_CONNECTOR_USB_B_H_

#include "Bus.h"

class USB_B : public Named {
public:
    USB_B(const std::string & name) : Named(name), NAME(p) {
    }

    Narray<Pin, 6> p;

    Pin & VBUS   = p[1];
    Pin & Dminus = p[2];
    Pin & Dplus  = p[3];
    Pin & GND    = p[4];
    Pin & Shield = p[5];
};

#endif /* PARTS_CONNECTOR_USB_B_H_ */
