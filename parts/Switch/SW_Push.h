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
// Low-level implementation of a push button.
// The button is simply a Wire ...
//
#ifndef _SW_Push_H_
#define _SW_Push_H_

#include "Wire.h"

class SW_Push : public Wire {
public:

    SW_Push(const std::string & name);

    void press(bool b);
    void toggle();

};

#endif // _SW_Push_H_
