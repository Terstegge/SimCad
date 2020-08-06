#ifndef _SST39SF040_H_
#define _SST39SF040_H_

#include "SST39SF040_skel.h"

class SST39SF040 : public SST39SF040_skel {
public:
    enum cmd_state { wait1, wait2, wait3, wait4, wait5, byte_prgm, erase };

    uint8_t  _mem[524288] = { 0 };
    bool _id_mode = false;
    int  _addr;
    int  _data;
    static cmd_state _state;
    
    SST39SF040(std::string name);

    void run_state_machine(int addr, int data);
};

#endif	// _SST39SF040_H_
