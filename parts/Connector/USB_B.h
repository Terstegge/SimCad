/*
 * USB_B.h
 *
 *  Created on: 07.05.2022
 *      Author: andreas
 */

#ifndef PARTS_CONNECTOR_USB_B_H_
#define PARTS_CONNECTOR_USB_B_H_

#include "Bus.h"

class USB_B {
public:
    USB_B(const std::string & name) {
    }

    Bus<6>	p;

    Pin & VBUS   = p[1];
    Pin & Dminus = p[2];
    Pin & Dplus  = p[3];
    Pin & GND    = p[4];
    Pin & Shield = p[5];
};

#endif /* PARTS_CONNECTOR_USB_B_H_ */
