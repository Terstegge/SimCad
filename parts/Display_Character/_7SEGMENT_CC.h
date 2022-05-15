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

