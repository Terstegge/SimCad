#ifndef _SRAM_32kb_DIP28_H_
#define _SRAM_32kb_DIP28_H_

#include "SRAM_32kb_DIP28_skel.h"

class SRAM_32kb_DIP28 : public SRAM_32kb_DIP28_skel {
public:

    uint8_t  _mem[32768] = { 0 };
    
    SRAM_32kb_DIP28(std::string name);
};

#endif	// _SRAM_32kb_DIP28_H_
