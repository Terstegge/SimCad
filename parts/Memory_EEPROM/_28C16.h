#ifndef _SRAM_32kb_DIP28_H_
#define _SRAM_32kb_DIP28_H_

#include "_28C16_skel.h"

class _28C16 : public _28C16_skel {
public:

    uint8_t  _mem[2048] = { 0 };

    _28C16(std::string name);

private:

    bool & on;
    int  _write_addr;
    bool _write_started;
};

#endif	// _SRAM_32kb_DIP28_H_
