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
#ifndef _SST39SF040_H_
#define _SST39SF040_H_

#include "SST39SF040_skel.h"

class SST39SF040 : public SST39SF040_skel {
public:
    enum cmd_state { wait1, wait2, wait3, wait4, wait5, byte_prgm, erase };

    uint8_t  _mem[524288] = { 0xff };
    bool _id_mode = false;
    int  _addr;
    int  _data;
    static cmd_state _state;
    
    SST39SF040(std::string name);

    void run_state_machine(int addr, int data);
};

#endif	// _SST39SF040_H_
