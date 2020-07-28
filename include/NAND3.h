#ifndef _NAND3_H_
#define _NAND3_H_

#include "NAND.h"

class NAND3 : public NAND<3> {
public:
    NAND3(const string & name=""): NAND(name)
    {
    }

};

#endif // _NAND3_H_
