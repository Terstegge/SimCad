#ifndef _NAND2_H_
#define _NAND2_H_

#include "NAND.h"

class NAND2 : public NAND<2> {
public:
    NAND2(const string & name=""): NAND(name)
    {
    }

};

#endif // _NAND2_H_
