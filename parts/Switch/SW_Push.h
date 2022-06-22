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
#ifndef _PARTS_SWITCH_SW_PUSH_H_
#define _PARTS_SWITCH_SW_PUSH_H_

#include "R.h"

class SW_Push : public R {
public:

    SW_Push(const std::string & name);

    void press(bool b);
    void toggle();

};

#endif // _PARTS_SWITCH_SW_PUSH_H_
