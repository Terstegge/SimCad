#include "SST39SF040.h"

SST39SF040::cmd_state SST39SF040::_state = wait1;

SST39SF040::SST39SF040(std::string name) : SST39SF040_skel(name) {
        // Attach address bus listener
        A.attach([this](NetSet * nets) {
            DATA_OUT = _mem[ A ];
        });
    
        // Latch address at start of write cycle
        // and latch data at falling edge
        WRITE.attach([this](NetSet * nets) {
            if ((State)WRITE == HIGH) {
                // Latch address
                _addr = A;
            }
            if ((State)WRITE == LOW) {
                // Latch data and process
                _data    = DATA_IN;
                DATA_OUT = DATA_IN;
                run_state_machine(_addr, _data);
            }
        });
        // Write out initial data
        DATA_OUT = _mem[A];
    } 	

    void SST39SF040::run_state_machine(int addr, int data) {
        switch (_state) {
            case wait1: {
                if (addr == 0x5555 && data == 0xaa) {
                    _state = wait2;
                } else
                if (data == 0xf0) {
                    _id_mode = false;        
                }
                break;
            }
            case wait2: {
                if (addr == 0x2aaa && data == 0x55) {
                    _state = wait3;
                } else {
                    _state = wait1;
                }
                break;
            }
            case wait3: {
                if (addr == 0x5555 && data == 0x80) {
                    _state = wait4;
                } else
                if (addr == 0x5555 && data == 0x90) {
                    _id_mode = true;
                    _state = wait1;
                } else
                if (addr == 0x5555 && data == 0xa0) {
                    _state = byte_prgm;
                } else
                if (addr == 0x5555 && data == 0xf0) {
                    _id_mode = false;
                    _state = wait1;
                } else {
                    _state = wait1;
                }
                break;
            }
            case wait4: {
                if (addr == 0x5555 && data == 0xaa) {
                    _state = wait5;
                } else {
                    _state = wait1;
                }
                break;
            }
            case wait5: {
                if (addr == 0x2aaa && data == 0x55) {
                    _state = erase;
                } else {
                    _state = wait1;
                }
                break;
            }
            case byte_prgm: {
                if (!(addr % 1024)) cout << "writing " << addr << " " << data << endl;
                _mem[ addr ] &= ~data;
                _state = wait1;
                break;
            }
            case erase: {
                if (addr == 0x5555 && data == 0x10) {
                    // Chip erase
                    cout << "Chip erase..." << endl;
                    for (int i=0; i < 524288; ++i) {
                        _mem[ i ] = 0xff;
                    }
                    _state = wait1;
                } else
                if (data == 0x30) {
                    // Sector erase
                    cout << "Sector erase..." << endl;
                    addr &= 0x7f000;
                    for (int i=0; i < 4096; ++i) {
                        _mem[ addr + i ] = 0xff;
                    }
                    _state = wait1;
                }
                break;
            }
        }
    }
