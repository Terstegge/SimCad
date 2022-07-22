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
#ifndef _PARTS_MEMORY_RAM_SRAM_32kb_DIP28_H_
#define _PARTS_MEMORY_RAM_SRAM_32kb_DIP28_H_

#include "SRAM_32kb_DIP28_skel.h"

class SRAM_32kb_DIP28 : public SRAM_32kb_DIP28_skel {
public:

    uint8_t  _mem[32768] = { 0 };

    SRAM_32kb_DIP28(std::string name);
};

#endif	// _PARTS_MEMORY_RAM_SRAM_32kb_DIP28_H_
