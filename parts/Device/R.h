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
// Implementation of a simple resistor.
//
#ifndef _INCLUDE_R_H_
#define _INCLUDE_R_H_

#include "TwoPole.h"

class R : public TwoPole {
    friend class R_POT;

public:
    R(const std::string & name, double r) : TwoPole(name), _R(r) {
    }

    double Rchar(double U) override {
        return _R;
    }

    double Ichar(double U) override {
        return U /_R;
    }

    inline void setR(double r) {
        _R = r;
        update();
    }

private:
    double _R;
};
#endif // _INCLUDE_R_H_
