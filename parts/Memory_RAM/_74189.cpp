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
//
#include "_74189.h"

_74189::_74189(std::string name)
    : _74189_skel(name), _write_addr(0), _write_started(false), on(U1.on) {

    // Attach address bus listener
    ADDR.attach([this](NetSet * nset) {
        if (!on) return;
        nOUT.set(_mem[ ADDR ], nset);
    });
    // Latch address at start of write cycle.
    // Write memory at end of write cycle
    WRITE.attach([this](NetSet * nset) {
        if (!on) return;
        if (WRITE) {
            // Latch address to write to
            _write_addr    = ADDR;
            _write_started = true;
        } else {
            // Store and output data
            if (!_write_started) return;
            _mem[_write_addr] = DATA;
            nOUT.set(DATA, nset);
            _write_started = false;
        }
    });
//    nOUT = _mem[ADDR];
}
