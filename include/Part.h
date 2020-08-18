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
// A part has a name, which is set in the part
// constructor.
//
#ifndef INCLUDE_PART_H_
#define INCLUDE_PART_H_

#include "Named.h"

struct Part : Named {

    Part(const string & name) : Named(name)
    {
    }

    virtual ~Part()
    {
    }

};

#endif /* INCLUDE_PART_H_ */
