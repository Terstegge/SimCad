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
// Low-level implementation of a simple switch.
// When on, both input states are propagated
// to the respective 'other' side.
//
#ifndef _SW_SPST_H_
#define _SW_SPST_H_

#include "TwoPole.h"

class SW_SPST : public TwoPole {

public:

    SW_SPST(const std::string & name) : TwoPole(name) {
        // Default: Switch open
        _G = 0;
    }

    void setOn(bool b) {
        _G = b ? INF : 0.0;
        update();
    }

};

#endif // _SW_SPST_H_
