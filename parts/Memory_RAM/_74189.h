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
#ifndef _PARTS_MEMORY_RAM_74189_H_
#define _PARTS_MEMORY_RAM_74189_H_

#include "_74189_skel.h"

class _74189 : public _74189_skel {
public:

    uint8_t  _mem[16] = { 0 };

    _74189(std::string name);

private:

    bool & on;
    int  _write_addr;
    bool _write_started;
};

#endif	// _PARTS_MEMORY_RAM_74189_H_
