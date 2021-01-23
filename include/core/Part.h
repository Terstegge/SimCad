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
// Virtual base class for all kinds of parts.
// Its only use is to have a common type for
// parts, so we can have part pointers.
// A part is 'Named'.
//
#ifndef INCLUDE_PART_H_
#define INCLUDE_PART_H_

#include "Named.h"
#include <string>

struct Part : Named {

    Part(const std::string & name) : Named(name) {
    }

    virtual ~Part() {
    }

};

#endif // INCLUDE_PART_H_
