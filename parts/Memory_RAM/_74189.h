#ifndef _74189_H_
#define _74189_H_

#include "_74189_skel.h"

class _74189 : public _74189_skel {
public:

    uint8_t  _mem[16] = { 0 };
    
    _74189(std::string name);
};

#endif	// _74189_H_
