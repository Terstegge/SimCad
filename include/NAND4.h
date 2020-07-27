#ifndef _NAND4_H_
#define _NAND4_H_

#include "NAND.h"

class NAND4 : public NAND<4> {
public:
    NAND4(const string & name=""): NAND(name)
    {
    }

};

#endif // _NAND4_H_
