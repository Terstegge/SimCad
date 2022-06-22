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
// Implementation of an ideal current source.
//
#ifndef _INCLUDE_ISOURCE_H_
#define _INCLUDE_ISOURCE_H_

#include "TwoPole.h"

class ISOURCE : public TwoPole {
public:

    ISOURCE(const std::string & name, double i) : TwoPole(name) {
        _Isrc = i;
    }

    double Rchar(double U) {
        return INF;
    }

    void setI(double i) {
        _Isrc = i;
        update();
    }
};

#endif // _INCLUDE_ISOURCE_H_
