#ifndef _NAND5_H_
#define _NAND5_H_

#include "NAND.h"

class NAND5 : public NAND<5> {
public:
    NAND5(const string & name=""): NAND(name)
    {
    }

};

#endif // _NAND5_H_
