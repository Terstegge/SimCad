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
// Low-level implementation of a simple switch.
// When on, both input states are propagated
// to the respective 'other' side.
//
#ifndef _SW_SPDT_H_
#define _SW_SPDT_H_

#include "Bus.h"
#include "Wire.h"

class SW_SPDT {
public:
    Bus<4>     p;

    enum { con21=0, con23=1 };

    SW_SPDT(const std::string & name);

    void set(int c);

private:
    Wire _wire21;
    Wire _wire23;
};

#endif // _SW_SPDT_H_
