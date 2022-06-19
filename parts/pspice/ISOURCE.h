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

    ISOURCE(const std::string & name, double i) : TwoPole(name), _I(i) {
    }

    double Rchar(double U) {
        return MAX_DBL;
    }

    double Ichar(double) {
        return _I;
    }

    void setI(double i) {
        _I = i;
        update();
    }

private:
    double _I;
};

#endif // _INCLUDE_ISOURCE_H_
