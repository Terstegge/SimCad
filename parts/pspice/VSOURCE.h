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
// Implementation of an ideal voltage source.
//
#ifndef _PARTS_PSPICE_VSOURCE_H_
#define _PARTS_PSPICE_VSOURCE_H_

#include "TwoPole.h"

class VSOURCE : public TwoPole {
public:

    VSOURCE(const std::string & name, double u) : TwoPole(name) {
        _Usrc = u;
    }

    double Rchar(double U) {
        return 0;
    }

    void setU(double u) {
        _Usrc = u;
        update();
    }
};

#endif // _PARTS_PSPICE_VSOURCE_H_
