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
#ifndef _PARTS_SWITCH_SW_DIP_X04_H_
#define _PARTS_SWITCH_SW_DIP_X04_H_

#include "SW_DIP_x04_skel.h"
#include <string>

class SW_DIP_x04 : public SW_DIP_x04_skel {
public:
    SW_DIP_x04(std::string name);

    void openSwitchesAt(int v);
    void closeSwitchesAt(int v);
};

#endif // _PARTS_SWITCH_SW_DIP_X04_H_
