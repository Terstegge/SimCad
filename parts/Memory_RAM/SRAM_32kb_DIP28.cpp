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
// Implementation of a 32kB RAM.
// When the Address Bus changes, data on the
// output Bus (DATA_OUT) is updated.
// Data is written at the end of a write cycle.
// For simplicity, the Address bus is not latched
// at the beginning of the write cycle, but instead
// read out at the same time as the data (DATA_IN).
//
#include "SRAM_32kb_DIP28.h"

SRAM_32kb_DIP28::SRAM_32kb_DIP28(std::string name) 
      : SRAM_32kb_DIP28_skel(name), _write_addr(0), _write_started(false) {
    
    // Attach address bus listener
    ADDR.attach([this](NetSet * nset) {
        if (!U1.on) return;
        DATA_OUT.set(_mem[ ADDR ], nset);
    });
    // Latch address at start of write cycle.
    // Write memory at end of write cycle
    WRITE.attach([this](NetSet * nset) {
        if (!U1.on) return;
        if (WRITE) {
            // Latch address to write to
            _write_addr    = ADDR;
            _write_started = true;
        } else {
            // Store and output data
            if (!_write_started) return;
            _mem[_write_addr] = DATA_IN;
            DATA_OUT.set(DATA_IN, nset);
            _write_started = false;
        }
    });
}
