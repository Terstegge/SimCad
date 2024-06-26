//
// Created by andreas on 23.06.24.
//

#ifndef _PARTS_CONNECTOR_CONN_01X01_H
#define _PARTS_CONNECTOR_CONN_01X01_H

#include "Bus.h"

class Conn_01x01 : public Named {
public:
    Conn_01x01(const std::string & name) : Named(name), NAME(p) {
    }

    Narray<Pin, 2> p;
};

#endif // _PARTS_CONNECTOR_CONN_01X01_H
