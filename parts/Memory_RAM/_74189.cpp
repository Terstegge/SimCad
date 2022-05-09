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
      : _74189_skel(name) {
    
    // Attach address bus listener
    ADDR.attach([this](NetSet * nset) {
        nOUT = _mem[ ADDR ];
    });
    // Write memory at end of write cycle
    WRITE.attach([this](NetSet * nset) {
        if (!WRITE) {
            _mem[ ADDR ] = DATA;
            nOUT         = DATA;
        }
    });
    // Write out initial data
    nOUT = _mem[ ADDR ];
}
