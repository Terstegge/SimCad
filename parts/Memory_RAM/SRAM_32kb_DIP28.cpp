///////////////////////////////////////////////
//
//  This file is part of
//   ____  ____  ___  ____  ___  ____  __  __
//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
//  (____/(____)\___/(____)(___/(____)(_/\/\_)
//
//  A simulation package for digital circuits
//
//  (c) 2020  A. Terstegge
//
///////////////////////////////////////////////
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
      : SRAM_32kb_DIP28_skel(name) {
    
    // Attach address bus listener
    A.attach([this](NetSet * nset) {
        DATA_OUT = _mem[ A ];
    });
    // Write memory at end of write cycle
    WRITE.attach([this](NetSet * nset) {
        if (WRITE == LOW) {
            _mem[ A ] = DATA_IN;
            DATA_OUT  = DATA_IN;
        }
    });
    // Write out initial data
    DATA_OUT = _mem[A];
}
