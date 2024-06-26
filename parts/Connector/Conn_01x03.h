//
// Created by andreas on 23.06.24.
//

#ifndef _PARTS_CONNECTOR_CONN_01X03_H
#define _PARTS_CONNECTOR_CONN_01X03_H

#include "Bus.h"

class Conn_01x03 : public Named {
public:
    Conn_01x03(const std::string & name) : Named(name), NAME(p) {
    }

    Narray<Pin, 4> p;
};

#endif // _PARTS_CONNECTOR_CONN_01X03_H
