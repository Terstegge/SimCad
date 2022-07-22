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
#ifndef _7SEGMENT_CC_H_
#define _7SEGMENT_CC_H_

#include "_7SEGMENT_CC_skel.h"
#include <iostream>
#include "LEDRef.h"

class _7SEGMENT_CC : public _7SEGMENT_CC_skel {
public:

    _7SEGMENT_CC(std::string name);

    char to_char();
    friend std::ostream & operator << (std::ostream & os, _7SEGMENT_CC & d);

private:

    LEDRef _value;

};

#endif	// _7SEGMENT_CC_H_

