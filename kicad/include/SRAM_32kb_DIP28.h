#ifndef _SRAM_32kb_DIP28_H_
#define _SRAM_32kb_DIP28_H_

#include "SRAM_32kb_DIP28_skel.h"

class SRAM_32kb_DIP28 : public SRAM_32kb_DIP28_skel {
public:

    uint8_t  _mem[32768] = { 0 };
    
    SRAM_32kb_DIP28(std::string name) 
      : SRAM_32kb_DIP28_skel(name) {
    
        // Attach address bus listener
        A.attach([this](NetSet * nets) {
            DATA_OUT = _mem[ A ];
        });
    
        // Write memory at end of write cycle
        WRITE.attach([this](NetSet * nets) {
            if ((State)WRITE == LOW) {
                _mem[ A ] = DATA_IN;
                DATA_OUT  = DATA_IN;
            }
        });
        // Write out initial data
        DATA_OUT = _mem[A];
    } 	

};

#endif	// _SRAM_32kb_DIP28_H_
