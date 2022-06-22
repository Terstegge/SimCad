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
#ifndef _PARTS_SWITCH_SW_DIP_X08_H_
#define _PARTS_SWITCH_SW_DIP_X08_H_

#include "SW_DIP_x08_skel.h"
#include <string>

class SW_DIP_x08 : public SW_DIP_x08_skel {
public:
    SW_DIP_x08(std::string name);

    void openSwitchesAt(int v);
    void closeSwitchesAt(int v);
};

#endif // _PARTS_SWITCH_SW_DIP_X08_H_
