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
// Low-level implementation of a simple switch.
// When on, both input states are propagated
// to the respective 'other' side.
//
#ifndef _SW_SPDT_H_
#define _SW_SPDT_H_

#include "SW_SPDT_skel.h"

class SW_SPDT : public SW_SPDT_skel {
public:

	enum { con21=0, con23=1 };

    SW_SPDT(const std::string & name);

    void set(int c);

};

#endif // _SW_SPDT_H_
