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
#ifndef _INCLUDE_BC338_H_
#define _INCLUDE_BC338_H_

#include "BJT_NPN.h"

class BC338 : public BJT_NPN {
public:

    BC338(const std::string & name) : BJT_NPN(name, PinOrder::CBE) {
        // Parameters may be changed here...
    }
};

#endif // _INCLUDE_BC338_H_
