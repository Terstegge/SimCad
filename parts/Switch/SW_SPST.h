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
// Low-level implementation of a simple switch.
// When on, both input states are propagated
// to the respective 'other' side.
//
#ifndef _PARTS_SWITCH_SW_SPST_H_
#define _PARTS_SWITCH_SW_SPST_H_

#include "R.h"

class SW_SPST : public R {
public:
    SW_SPST(const std::string & name);

    void setOn(bool b);
    void toggle();

};

#endif // _PARTS_SWITCH_SW_SPST_H_
