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
#include "_74189.h"

_74189::_74189(std::string name)
    : _74189_skel(name), _write_addr(0), _write_started(false) {

    // Attach address bus listener
    ADDR.attach([this](NetSet * nset) {
        if (!U1.on) return;
        nOUT.set(_mem[ ADDR ], nset);
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
            _mem[_write_addr] = DATA;
            nOUT.set(DATA, nset);
            _write_started = false;
        }
    });
}
