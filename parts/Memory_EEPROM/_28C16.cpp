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
#include "_28C16.h"

_28C16::_28C16(std::string name)
    : _28C16_skel(name), _write_addr(0), _write_started(false) {
    
    // Attach address bus listener
    ADDR.attach([this](NetSet * nset) {
        DATA_OUT.set(_mem[ ADDR ], nset);
    });
    // Latch address at start of write cycle.
    // Write memory at end of write cycle
    WRITE.attach([this](NetSet * nset) {
        if (WRITE) {
        	// Latch address to write to
        	_write_addr    = ADDR;
        	_write_started = true;
        } else {
        	// Store and output data
        	if (!_write_started) return;
        	_mem[ _write_addr ] = DATA_IN;
            DATA_OUT.set(DATA_IN, nset);
            _write_started = false;
        }
    });
    // Write out initial data
    DATA_OUT = _mem[ ADDR ];
}
