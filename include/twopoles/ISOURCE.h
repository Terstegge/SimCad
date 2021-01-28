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
// Implementation of a ideal current source.
//
#ifndef _INCLUDE_ISOURCE_H_
#define _INCLUDE_ISOURCE_H_

#include "TwoPole.h"

class ISOURCE : public TwoPole {
public:
    ISOURCE(const std::string & name, float i) : TwoPole(name), _I(i) {
        setG ( 0 );
    }

    void p1_callback() override {
        p[2].Id = -_I;
    }
    void p2_callback() override {
        p[1].Id = +_I;
    }

    void setI(float i) {
        _I = i;
    }

private:
    float _I;
};

#endif // _INCLUDE_VSOURCE_H_
